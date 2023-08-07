
#include"stm32f10x.h"

void SysClockConfig (void){
	
	//HSE Clock on
	
	RCC->CR |= RCC_CR_HSEON;
	
	// HSE clock ready
	while(!(RCC->CR & RCC_CR_HSERDY));
	
	//Enable power & voltagevregulator
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	
	
	


}

int main(void)
{
	while(1){
	
	
	
	}
		
}
