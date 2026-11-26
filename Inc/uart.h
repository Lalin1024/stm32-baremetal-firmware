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

void disable_gnss(uint8_t  *arr,uint8_t size);

#endif /* UART_H_ */
