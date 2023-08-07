#include<stm32f446xx.h>

int main(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	
	GPIOA->MODER |= 0x400;
	while(1){
		GPIOA->BSRR |= GPIO_BSRR_BS5;
		for(int i= 0; i<1000000; i++);
		GPIOA->BSRR |= GPIO_BSRR_BS5;
		for(int i= 0; i<1000000; i++);
	}
	
}
