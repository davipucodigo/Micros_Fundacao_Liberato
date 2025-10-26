
#include "stm32f4xx.h"
#include "YAPP_4324_davi.h"



int main () {
	RCC->AHB1ENR = 0x87;
	// MODER C
	GPIOC->MODER &= 0b0000;
	//                P3P2P1P0
	GPIOC->MODER |= 0b01010101;

	// CONFIG TIMER
	RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
	TIM10->PSC= PSC_4324_davi;
	TIM10->ARR= ARR_4324_davi;
	TIM10->CR1 |= TIM_CR1_CEN;

	while (1) {
		pisca4324_davi(GPIOC,2,3,TIM10);
	}
}
