
/*
CABEÇALHO
Metodo usado: Bare Metal
Autores: Davi Sant'Anna, Eduardo, Lorenzo
Ano: 2025
*/
#include "stm32g0xx.h"

int main () {

	//VARIAVEIS
	int conta_coluna  = 0;
	int sensor;
	int seleciona_imagem = 0; //Mude entre 0 e 1 para selecionar a imagem1 ou imagem2
	int images [5][2] = {
	//Display 5x7
	//Image1
	0b1000010,
	0b0100100,
	0b0011000,
	0b0011000,
	0b0100100,
	0b1000010,
	
	//Image2
	0b0111100,
	0b0100100,
	0b0100100,
	0b0100100,
	0b0100100,
	0b0100100,
	0b0111100
	}

	//CLOCK GERAL
	RCC->IOPENR = 0x3f;

	//GPIOD ENTRADA Botão pull-up externo
	GPIOD->MODER &= 0b00;

	// ==== SAIDAS GPIOC COLUNAS 5
	//               	P4P3P2P1P0
	GPIOC->MODER &= ~(0b1111111111); // zerando
	GPIOC->MODER |= 0b0101010101; // definindo como saida

	// ==== SAIDAS GPIOB LINHAS 7
	//                  P6P5P4P3P2P1P0
	GPIOB->MODER &= ~(0b11111111111111); // zerando
	//                P6P5P4P3P2P1P0
	GPIOB->MODER |= 0b01010101010101; // Saida

	//TIM14 configurando
	RCC->APBENR2|=RCC_APBENR2_TIM14EN; //clock
	TIM14->PSC=(1600-1); //presscaller
	TIM14->ARR=(444); //numero de corte
	TIM14->CR1=TIM_CR1_CEN; //ativa o timer
	
	while (1) {

		sensor = GPIOD->IDR & 0b1; // le botao

		if (sensor == 0b1) {
			GPIOB->ODR &= 0b1111111;
		}else {
			GPIOB->ODR &= 0b0000000;
			GPIOB->ODR |= 0b1000001;
		}

		// logica de atualizacao TIM
		if(TIM14->SR & TIM_SR_UIF){
			TIM14->SR &= ~TIM_SR_UIF;
			
			conta_coluna++;
			switch (conta_coluna) {
				case 0: 
					// =============================================================== COLUNAS 1 - PC0
					GPIOC->ODR &= 0x1F; // 0001 1111 TORNA A 1 todos os bits da COLUNA	
					//              43210
					GPIOC->ODR |= 0b11110<<0;

					// =============================================================== LINHAS
					GPIOB->ODR &= 0x00;
					GPIOB->ODR |= images[0][seleciona_imagem];
					break;
				case 1: 
					// =============================================================== COLUNAS 2 - PC1
					GPIOC->ODR &= 0x1F;
					GPIOC->ODR |= 0b11110<<1;
					
					// ===============================================================> LINHAS
					GPIOB->ODR &= 0x00;
					GPIOB->ODR |= images[1][seleciona_imagem];
					break;
				case 2: 
					// ===============================================================> COLUNAS 3 - PC2
					GPIOC->ODR &= 0x1F;
					GPIOC->ODR |= 0b11110<<2;
					
					// ===============================================================> LINHAS
					GPIOB->ODR &= 0x00;
					GPIOB->ODR |= images[2][seleciona_imagem];
					break;
				case 3: 
					// ===============================================================> COLUNAS 4 - PC3
					GPIOC->ODR &= 0x1F;
					GPIOC->ODR |= 0b11110<<3;

					// ===============================================================> LINHAS
					GPIOB->ODR &= 0x00;
					GPIOB->ODR |= images[0][seleciona_imagem];
					break;
				case 4:
					// ===============================================================> COLUNAS 5 - PC4
					GPIOC->ODR &= 0x1F;
					GPIOC->ODR |= 0b11110<<4;
					
					// ===============================================================> LINHAS
					GPIOB->ODR &= 0x00;
					GPIOB->ODR |= images[4][seleciona_imagem];
				case 5:
					conta_coluna = 0;
					break;
			}
		}
	}
}
