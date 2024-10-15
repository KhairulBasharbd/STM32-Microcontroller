#include "stm32f4xx.h"
#include<stdio.h>

uint8_t I2C_ReadRegister(uint8_t deviceAddr, uint8_t regAddr);

uint8_t BCD_to_Decimal(uint8_t bcd);

void read_DS3231_time(uint8_t* hours, uint8_t* minutes, uint8_t* seconds);
