#include "stm32f4xx.h"
#include<stdio.h>

#define I2C_ADDRESS_DS3231   0x68  // I2C address for DS3231 RTC module


uint8_t I2C_ReadRegister(uint8_t deviceAddr, uint8_t regAddr) {
    uint8_t data;

    // Wait until I2C is not busy
    while (I2C1->SR2 & I2C_SR2_BUSY);

    // Start I2C communication
    I2C1->CR1 |= I2C_CR1_START;

    // Wait for start bit generation
    while (!(I2C1->SR1 & I2C_SR1_SB));

    // Send the address with the write bit
    I2C1->DR = (deviceAddr << 1) & 0xFE;

    // Wait for address to be sent
    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    // Clear ADDR flag by reading SR1 and SR2
    (void)I2C1->SR1;
    (void)I2C1->SR2;

    // Send the register address
    I2C1->DR = regAddr;

    // Wait for register address to be sent
    while (!(I2C1->SR1 & I2C_SR1_TXE));

    // Repeat start condition and send the address with the read bit
    I2C1->CR1 |= I2C_CR1_START;

    // Wait for start bit generation
    while (!(I2C1->SR1 & I2C_SR1_SB));

    // Send the address with the read bit
    I2C1->DR = (deviceAddr << 1) | 0x01;

    // Wait for address to be sent
    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    // Clear ADDR flag by reading SR1 and SR2
    (void)I2C1->SR1;
    (void)I2C1->SR2;

    // Wait for data to be received
    while (!(I2C1->SR1 & I2C_SR1_RXNE));

    // Read the data
    data = I2C1->DR;

    // Stop I2C communication
    I2C1->CR1 |= I2C_CR1_STOP;

    return data;
}

uint8_t BCD_to_Decimal(uint8_t bcd) {
    return ((bcd / 16 * 10) + (bcd % 16));
}

void read_DS3231_time(uint8_t* hours, uint8_t* minutes, uint8_t* seconds) {
    uint8_t seconds_bcd = I2C_ReadRegister(I2C_ADDRESS_DS3231, 0x00); // Read seconds register
    uint8_t minutes_bcd = I2C_ReadRegister(I2C_ADDRESS_DS3231, 0x01); // Read minutes register
    uint8_t hours_bcd = I2C_ReadRegister(I2C_ADDRESS_DS3231, 0x02);   // Read hours register

    *seconds = BCD_to_Decimal(seconds_bcd);
    *minutes = BCD_to_Decimal(minutes_bcd);
    *hours = BCD_to_Decimal(hours_bcd);
}