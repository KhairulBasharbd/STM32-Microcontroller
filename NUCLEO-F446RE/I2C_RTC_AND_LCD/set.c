
#include"set.h"


void I2C1_Write(uint8_t address, uint8_t reg, uint8_t *data, uint8_t size) {
    // Start condition
    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB));  // Wait for start condition generated

    // Send address with write mode
    I2C1->DR = address;
    while (!(I2C1->SR1 & I2C_SR1_ADDR));  // Wait for address to be acknowledged
    (void)I2C1->SR2;  // Clear ADDR flag by reading SR2

    // Send register address
    I2C1->DR = reg;
    while (!(I2C1->SR1 & I2C_SR1_TXE));  // Wait until data register is empty

    // Send the data
    for (int i = 0; i < size; i++) {
        I2C1->DR = data[i];
        while (!(I2C1->SR1 & I2C_SR1_TXE));  // Wait until data register is empty
    }

    // Stop condition
    I2C1->CR1 |= I2C_CR1_STOP;
}

// Convert normal decimal numbers to binary-coded decimal
uint8_t decToBcd(int val) {
    return (uint8_t)((val / 10 * 16) + (val % 10));
}

// Function to set time on DS3231
void Set_Time(uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year) {
    uint8_t set_time[7];
    set_time[0] = decToBcd(sec);
    set_time[1] = decToBcd(min);
    set_time[2] = decToBcd(hour);
    set_time[3] = decToBcd(dow);
    set_time[4] = decToBcd(dom);
    set_time[5] = decToBcd(month);
    set_time[6] = decToBcd(year);

    I2C1_Write(0xD0, 0x00, set_time, 7);  // Write to DS3231 at address 0xD0
}


