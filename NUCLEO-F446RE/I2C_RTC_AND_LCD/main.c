#include "stm32f4xx.h"
#include<stdio.h>
#include"set.h"
#include"i2c-lcd.h"
#include"gettime.h"


void I2C_Init(void) {
    // Enable GPIOB clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // Configure PB8 and PB9 for I2C1 (Alternate function, open-drain, pull-up)
    GPIOB->MODER &= ~(GPIO_MODER_MODE8 | GPIO_MODER_MODE9);
    GPIOB->MODER |= (GPIO_MODER_MODE8_1 | GPIO_MODER_MODE9_1); // Alternate function mode
    GPIOB->OTYPER |= (GPIO_OTYPER_OT8 | GPIO_OTYPER_OT9); // Open-drain
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD8 | GPIO_PUPDR_PUPD9);
    GPIOB->PUPDR |= (GPIO_PUPDR_PUPD8_0 | GPIO_PUPDR_PUPD9_0); // Pull-up
    GPIOB->AFR[1] |= (4 << GPIO_AFRH_AFSEL8_Pos) | (4 << GPIO_AFRH_AFSEL9_Pos); // AF4 for I2C1

    // Enable I2C1 clock
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    // Reset I2C1
    RCC->APB1RSTR |= RCC_APB1RSTR_I2C1RST;
    RCC->APB1RSTR &= ~RCC_APB1RSTR_I2C1RST;

    // Configure I2C1
    I2C1->CR1 = 0; // Clear PE bit (disable I2C)
    I2C1->CR2 = 16; // Set peripheral clock frequency (16 MHz)
    I2C1->CCR = 80; // Configure clock control register (100 kHz standard mode)
    I2C1->TRISE = 17; // Configure maximum rise time
    I2C1->CR1 |= I2C_CR1_ACK; // Enable ACK
    I2C1->CR1 |= I2C_CR1_PE;  // Enable I2C
}





int main(void) {
    I2C_Init();
		//lcd_init() ;
	
    uint8_t hours, minutes, seconds;
	
		//Set_Time(00,07,05,5,26,9,24);
		char buffer[15];

	while (1) {
        read_DS3231_time(&hours, &minutes, &seconds);
			

				sprintf(buffer,"%02d-%02d-%02d",seconds,minutes,hours);

//				lcd_put_cur(0,0);
//				lcd_send_string (buffer);

        for (volatile int i = 0; i < 1000000; i++); // Simple delay
    }
}
