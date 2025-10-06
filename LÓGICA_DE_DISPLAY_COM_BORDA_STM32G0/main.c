/*
CABEÇALHO
Metodo usado: Bare Metal
Autores: Davi Sant'Anna
Ano: 2025
*/
#include "stm32g0xx.h"

//TIM14 configurando =======================|
// 20ms recomendado.
RCC->APBENR2|=RCC_APBENR2_TIM14EN; //clock
TIM14->PSC=(16-1); //presscaller
TIM14->ARR=(18823 - 1); //numero de corte
TIM14->CR1=TIM_CR1_CEN; //ativa o timer
// =========================================|

int main() {
    while (1) {
        if(TIM14->SR & TIM_SR_UIF){
			TIM14->SR &= ~TIM_SR_UIF;
			//Ação controlada por TIMER.
		}
    }
}