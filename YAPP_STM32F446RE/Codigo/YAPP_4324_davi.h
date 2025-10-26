/*
 * YAPP_4324_davi.h
 *
 *  Created on: Oct 26, 2025
 *      Author: vizlab_manoela
 */

#ifndef SRC_YAPP_4324_DAVI_H_
#define SRC_YAPP_4324_DAVI_H_

//#include "stm32f4xx.h"

/*
 *  Definicoes de constantes
 */

/* Configuracao inicial timer */
#define PSC_4324_davi (128)  // Valor inicial PSC timer
#define ARR_4324_davi (15625)     // Valor inicial ARR timer

/* Prototipos */

/* Funcao principal */
void pisca4324_davi(GPIO_TypeDef *Gpio, uint16_t  pinA, uint16_t  pinB, TIM_TypeDef *Tim );

/* Funcoes auxiliares */

#endif /* SRC_YAPP_4324_DAVI_H_ */
