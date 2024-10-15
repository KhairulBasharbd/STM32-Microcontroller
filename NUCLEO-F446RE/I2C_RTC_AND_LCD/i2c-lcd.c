#include "i2c-lcd.h"
#include "stm32f4xx.h"
#include "i2c-lcd.h"

#define SLAVE_ADDRESS_LCD 0x4E  // I2C address for the LCD

// Low-level I2C write function for LCD
void I2C1_Write_lcd(uint8_t address, uint8_t reg, uint8_t *data, uint8_t size) {
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

// Custom delay function (busy loop)
void delay_ms(uint32_t ms) {
    // Assuming SysTick is running at 1ms per tick
    uint32_t current_ticks = SysTick->VAL;
    while ((SysTick->VAL - current_ticks) < ms * 1000) { }
}

void lcd_send_cmd(char cmd) {
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (cmd & 0xF0);
    data_l = ((cmd << 4) & 0xF0);
    data_t[0] = data_u | 0x0C;  // en=1, rs=0
    data_t[1] = data_u | 0x08;  // en=0, rs=0
    data_t[2] = data_l | 0x0C;  // en=1, rs=0
    data_t[3] = data_l | 0x08;  // en=0, rs=0
    I2C1_Write_lcd(SLAVE_ADDRESS_LCD, 0, data_t, 4);  // Use low-level I2C function
}

void lcd_send_data(char data) {
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (data & 0xF0);
    data_l = ((data << 4) & 0xF0);
    data_t[0] = data_u | 0x0D;  // en=1, rs=1
    data_t[1] = data_u | 0x09;  // en=0, rs=1
    data_t[2] = data_l | 0x0D;  // en=1, rs=1
    data_t[3] = data_l | 0x09;  // en=0, rs=1
    I2C1_Write_lcd(SLAVE_ADDRESS_LCD, 0, data_t, 4);  // Use low-level I2C function
}

void lcd_clear(void) {
    lcd_send_cmd(0x80);
    for (int i = 0; i < 70; i++) {
        lcd_send_data(' ');
    }
}

void lcd_put_cur(int row, int col) {
    switch (row) {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }
    lcd_send_cmd(col);
}

void lcd_init(void) {
    // 4-bit initialization
    delay_ms(50);  // Wait for >40ms
    lcd_send_cmd(0x30);
    delay_ms(5);   // Wait for >4.1ms
    lcd_send_cmd(0x30);
    delay_ms(1);   // Wait for >100us
    lcd_send_cmd(0x30);
    delay_ms(10);
    lcd_send_cmd(0x20);  // 4bit mode
    delay_ms(10);

    // Display initialization
    lcd_send_cmd(0x28);  // Function set --> DL=0 (4-bit mode), N=1 (2 line display), F=0 (5x8 characters)
    delay_ms(1);
    lcd_send_cmd(0x08);  // Display on/off control --> D=0, C=0, B=0 ---> display off
    delay_ms(1);
    lcd_send_cmd(0x01);  // Clear display
    delay_ms(1);
    lcd_send_cmd(0x06);  // Entry mode set --> I/D=1 (increment cursor), S=0 (no shift)
    delay_ms(1);
    lcd_send_cmd(0x0C);  // Display on/off control --> D=1, C and B=0 (cursor and blink off)
}

void lcd_send_string(char *str) {
    while (*str) {
        lcd_send_data(*str++);
    }
}
