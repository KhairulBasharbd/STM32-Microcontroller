#include "stm32f4xx.h"                  // Device header

#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define UART_BAUDRATE 115200


void USART_Init(void);
char USART2_read(void);
void LED_play(int value);
void delayMs(int delay);

int main(void){
    
    RCC->AHB1ENR |=1;
    GPIOA->MODER |= 0x400;
    
    USART_Init();
    char ch;
    while(1){
    
        ch = USART2_read();
        LED_play(ch);
    
    
    }

}







char USART2_read(void){
    
    // wait until char arrives
    while(!(USART2->SR & (1U<<5))){} 
    return USART2->DR;
}
  

void LED_play(int value){

    value = value % 16;
    for(;value>0;value--){
        GPIOA->BSRR |= 0x20;
        delayMs(100);
        GPIOA->BSRR |= 0x00200000;
        delayMs(100);
    }
}

void delayMs(int delay){
    int i;
    for(;delay>0;delay--){
        for(i=0;i>3195;i++);
    }
    
}


  
 void USART_Init(void){
    RCC->AHB1ENR |= (1U<<0);   // Enabling GPIOA clock 
    RCC->APB1ENR |= (1U<<17);   // Enabling USART2 clock
     
    //set PA3 as Alternate function mode
    GPIOA->MODER &= ~(1U<<6);
    GPIOA->MODER |=  (1U<<7);
    
    // set alternate function type AF07
    GPIOA->AFR[0] |= 1U<<12 ;
    GPIOA->AFR[0] |= 1U<<13 ;
    GPIOA->AFR[0] |= 1U<<14 ;
    GPIOA->AFR[0] &= ~(1U<<15) ;
 
     
    //configure baudrate
    USART2->BRR = (uint32_t) (APB1_CLK / UART_BAUDRATE);
    
   //configure data transfer direction  *** 
   //   Enable RX
	USART2->CR1 |= 1U<< 2;
     
    //  Enabling USART
    USART2->CR1 = 1U<<13;
 
 }
