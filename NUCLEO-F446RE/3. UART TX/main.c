#include<stdint.h>
#include<stdio.h>
#include<stm32f446xx.h>

#define GPIOAEN (1U<<0)
#define UART2EN (1U<<17)

#define CR1_TE (1U<<3)
#define CR1_UE (1U<<13)
#define SR_TXE (1U<<7)

#define SYS_FREQ 45000000
#define APB1_CLK SYS_FREQ

#define UART_BAUDRATE 115200

void uart2_tx_init(void);
void uart2_write(uint8_t ch);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);




int main(void){
	
	uart2_tx_init();
	
	while(1){
		
		uart2_write('z');
		for(int i=0;i<1000000;i++){}
	}

}





void uart2_write(uint8_t ch){

	//********************************************************
	// make sure tranmit data register is empty
	while(!(USART2->SR & SR_TXE)){}
	
	//write to the transmit data register
	USART2->DR = (ch & 0xFF);
		

}


void uart2_tx_init(void){
	
	//***************configure GPIO PIN****************
	//enabling clock access on GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	
	//set PA2 as Alternate function mode
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);
	
	// set alternate function type AF07
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);
	
	
	//***************configure UART****************
	//enable clock access to usart2
	RCC->APB1ENR |= UART2EN;
	
	//configure baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);
	
	//configure data transfer direction
	USART2->CR1 |=CR1_TE;
	
	//Enable uart module
	USART2->CR1 |=CR1_UE;
	
}



static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate){
	
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);

}



static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){
	
	//uint16_t abc = ((PeriphClk + (BaudRate/2))/ BaudRate);
	
	//printf("abc");

	return (uint16_t)((PeriphClk + (BaudRate/2))/ BaudRate);
	
	
}




