/*
 * YAPP_43xx_ee.c
 *
 * Definicao da funcao pisca
 * Substituir xx pela identificacao da turma.
 * Substituir ee pela identificacao da equipe/grupo
 * A funcao pisca eh parametrizada, recebendo atraves dos parametros qual dos perifericos TIM e GPIO serao utilizados
 * Utilizar somente um periferico TIM, se houver necessidade de mais temporizadores, implementar por software
 * A funcao nao deve "segurar" ou "travar" ou atrasar o processamento.
 *      Author: Marcos Zuccolotto
 */


#include "stm32f4xx.h"
#define Npadroes 36

//Variaveis
int conta = 0;

int padrao[Npadroes] = {
	0b01,
	0b00,
	0b01,
	0b00,
	0b01,
	0b10,
	0b00,
	0b10,
	0b00,
	0b10,
	0b01,
	0b00,
	0b01,
	0b00,
	0b01,
	0b10,
	0b00,
	0b10,
	0b00, // == Proximo padrão
	0b10,
	0b01,
	0b10,
	0b01,
	0b10,
	0b01,
	0b10,
	0b01,
	0b10,
	0b01,
	0b10,
	0b01,
	0b10,
	0b01,
	0b10,
	0b01,
	0b10
};

void pisca4324_davi(GPIO_TypeDef *Gpio, uint16_t  pinA, uint16_t  pinB, TIM_TypeDef *Tim )
/*
 * Gpio - aponta para GPIO utilizado
 * pinA e pinK - pinos conectados aos leds
 * Tim - ponteiro para o TIM utilizado
 */
{
		Tim->PSC= 128;
		if (Tim->SR & TIM_SR_UIF) {
			Tim->SR &=~TIM_SR_UIF;

			if (conta == Npadroes) {
				conta=0;
			}else {

				// 8Hz
				if (conta <= 19) Tim->ARR = 15625;
				// 12Hz
				if ( conta > 19 && conta <= 28) Tim->ARR = 10416;
				// 30Hz
				if (conta > 28) Tim->ARR = 4166;

				Gpio->ODR &= 0b00;
				Gpio->ODR |= ( padrao[conta]&0b01 )<<pinA;
				Gpio->ODR |= (( padrao[conta]&0b10)>>1 )<<pinB;
				conta++;
			}
		}


}
