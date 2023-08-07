#include<stm32f446xx.h>


int main(void){

	RCC->AHB1ENR |= 1U<<0;
	
	GPIOA->MODER |= 1U<<10;
	GPIOA->MODER &= ~(1U<<11);
	
	while(1){
		
		GPIOA->ODR |= 1U<<5;
		for(int i=0;i<1000000;i++){}
		
		GPIOA->ODR &= ~(1U<<5);
		for(int i=0;i<100000;i++){}
	
	}

}
