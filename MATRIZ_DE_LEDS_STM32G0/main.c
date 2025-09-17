
/*
CABEÇALHO
Metodo usado: Bare Metal
Autores: Davi Sant'Anna, Eduardo, Lorenzo
Ano: 2025
*/
#include "stm32g0xx.h"

int main () {

	//VARIAVEIS
	int conta_coluna = 0;
	int sensor = 0;
	int seleciona_imagem = 0; //Mude entre 0 e 1 para selecionar a imagem1 ou imagem2
	int images[5] = {
			//imagens Linhas
			0b1100000,
			0b1111110,
			0b0111111,
			0b1111110,
			0b1100000
	};
	int colunas[5]={
			0b11110,
			0b11101,
			0b11011,
			0b10111,
			0b01111
	};

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
	TIM14->ARR=(100); //numero de corte
	TIM14->CR1=TIM_CR1_CEN; //ativa o timer

	// Fout = Fclock / PSC / ARR

	while (1) {

		sensor = GPIOD->IDR & 0b1; // le botao

		// logica de atualizacao TIM
		if(TIM14->SR & TIM_SR_UIF){
			TIM14->SR &= ~TIM_SR_UIF;
			GPIOB->ODR &= 0x00;
			GPIOC->ODR &= 0b00000;

			GPIOC->ODR |= (colunas[conta_coluna]);

			GPIOB->ODR |= (images[conta_coluna]);
			conta_coluna++;
			if(conta_coluna>4){
				conta_coluna=0;
			}
		}
	}
}

