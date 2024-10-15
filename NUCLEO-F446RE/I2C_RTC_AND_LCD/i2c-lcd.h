
#include "stm32f4xx.h"
void I2C1_Write_lcd(uint8_t address, uint8_t reg, uint8_t *data, uint8_t size) ;

void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_clear(void);
void lcd_put_cur(int row, int col);
void lcd_init(void) ;

void lcd_send_string(char *str);

void delay_ms(uint32_t ms) ;
