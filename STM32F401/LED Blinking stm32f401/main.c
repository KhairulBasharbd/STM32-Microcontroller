   
	 #include"stm32f401xc.h"
	 
	 
	void SysClockConfig(void)
	{
		
		#define PLL_M 25
		#define PLL_N 168
		#define PLL_P 0
		
		// 1. 
		RCC->CR |= RCC_CR_HSEON;
		while(!(RCC->CR & RCC_CR_HSERDY));
		
		// 2. 
		RCC->APB1ENR |= RCC_APB1ENR_PWREN;
		PWR->CR |= PWR_CR_VOS;
		
		// 3. 
		FLASH->ACR |= FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_2WS;
		
		// 4.
		RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
		RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
		RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;
		
		// 5. 
		RCC->PLLCFGR = (PLL_M << 0) | (PLL_N <<6) | (PLL_P << 16) | (RCC_PLLCFGR_PLLSRC_HSE);
		
		// 6. 
		RCC->CR |= RCC_CR_PLLON;
		while(!(RCC->CR & RCC_CR_PLLRDY));
		
		// 7. 
		RCC->CFGR |= RCC_CFGR_SW_PLL;
		while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
	 
	}
	
	
	
	void GPIO_Config(void){
	  // 1.
		RCC->AHB1ENR |= (1<<0);
		
		// 2.
		GPIOA->MODER |= (1<<10);
		
		// 3. 
		GPIOA->OTYPER =0;
		GPIOA->OSPEEDR =0;
	
	
	}
	
	void delay(uint32_t time){
		while(time--);
	
	}
	
	 
	 int main(void){
		 
		 SysClockConfig();
		 GPIO_Config();
	 
	 while(1){
		GPIOA->BSRR |= (1<<5);\
		delay(10000000);
		GPIOA->BSRR |= ((1<<5) << 16);
		delay(1000000);
		 
	 
	 }
	 
 }


	 