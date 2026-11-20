/*
 * uart.h
 *
 *  Created on: Nov 17, 2026
 *      Author: LalinPrasadC
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f401xc.h"

void uart_init();

static void setBudRate(USART_TypeDef* USART,uint32_t baud);

#endif /* UART_H_ */
