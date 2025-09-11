
/*
CABEÇALHO
Metodo usado: Bare Metal
Autores: Davi Sant'Anna, Eduardo, Lorenzo
Ano: 2025
*/
#include "stm32g0xx.h"

int main () {

	//VARIAVEIS
	int conta_coluna;
	int sensor;

	//CLOCK GERAL
	RCC->IOPENR = 0x3f;

	//GPIOD ENTRADA Botão pull-up externo
	GPIOD->MODER &= 0b00;

	// ==== SAIDAS GPIOC
	//               	P4P3P2P1P0
	GPIOC->MODER &= ~(0b1111111111); // zerando
	GPIOC->MODER |= 0b0101010101; // definindo como saida

	// ==== SAIDAS GPIOB
	//                  P6P5P4P3P2P1P0
	GPIOB->MODER &= ~(0b11111111111111); // Entrada >> Saida
	//                P6P5P4P3P2P1P0
	GPIOB->MODER |= 0b01010101010101; // Saida

	//TIM14 configurando
	RCC->APBENR2|=RCC_APBENR2_TIM14EN; //clock
	TIM14->PSC=(1600-1); //presscaller
	TIM14->ARR=(444); //numero de corte
	TIM14->CR1=TIM_CR1_CEN; //ativa o timer

	while (1) {

		sensor = GPIOD->IDR & 0b1;

		if (sensor == 0b1) {
			GPIOB->ODR &= 0b1111111;
		}else {
			GPIOB->ODR &= 0b0000000;
			GPIOB->ODR |= 0b1000001;
		}

	if(TIM14->SR & TIM_SR_UIF){
		TIM14->SR &= ~TIM_SR_UIF;
		
		conta_coluna++;
		if(conta_coluna==2) conta_coluna=0;

		GPIOB-> ODR|= 0b1111111;

		if(conta_coluna==0) GPIOC-> ODR&= 0b00000;
		if(conta_coluna==1) GPIOC-> ODR|= 0b11111;

		}
	}
}

