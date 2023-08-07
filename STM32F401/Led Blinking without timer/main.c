#include"stm32f401xc.h"

int main(void){

	RCC->AHB1ENR |=0x00000001;
	GPIOA->MODER |=0x00000400;

	
	while(1){
		
		
		GPIOA->ODR |= 0x00000020;
		while(100000--){
		
		
		}
		
		//delays(10000);
		
		GPIOA->ODR &=~(0x00000020);
	}


}

