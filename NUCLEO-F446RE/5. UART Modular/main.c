#include<stdint.h>
#include<stdio.h>
#include<stm32f446xx.h>

#include "uart.h"



int main(void){
	
	uart2_tx_init();
	
	while(1){
		
		uart2_write('z');
		
		//printf("Hello \n\r");
		
		for(int i=0;i<1000000;i++){}
			
	}

}





