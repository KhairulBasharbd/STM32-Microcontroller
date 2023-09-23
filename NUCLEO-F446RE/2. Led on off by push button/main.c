#include<stm32f446xx.h>

#define GPIOAEN 1U<<0
#define GPIOCEN 1U<<2

#define PIN13  1U<<13
#define PIN5  1U<<5


int main(void){
	
	// Enabling clock for gpioA and C
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;
	
	//Enabling port A as output and C as input mode 

	
	
	
	GPIOA->MODER |= 1U<<10;
	GPIOA->MODER &= ~(1U<<11);
	
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);
	
	while(1){
		
		
		if(GPIOC->IDR & PIN13){
			//turn on LED
			GPIOA->BSRR |= (1U<<5);
		}
		else{
			////turn off LED
			
			GPIOA->BSRR |= 1U<<21;
		}
	
	}

}
