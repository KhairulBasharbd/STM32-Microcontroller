#include"stm32f401xc.h"

int main(void){

	RCC->AHB1ENR |=0x00000001;
	GPIOA->MODER |=0x00000400;

	
	while(1){
		
		
		GPIOA->ODR |= 0x00000020;
		for(int i=0;i<1000000;i++){}
		
		//delays(10000);
		
		GPIOA->ODR &= ~(1U <<5);
		for(int i=0;i<1000000;i++){}
	}


}

