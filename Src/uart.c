/*
 * uart.c
 *
 *  Created on: Nov 17, 2026
 *      Author: LalinPrasadC
 */


#include<uart.h>

#define SYSCLK		42000000U
#define USART2_EN	(1U<<17)
#define	GPIOA_EN	(1U<<0)

void uart_init()
{
	RCC->APB1ENR|=USART2_EN;

	RCC->AHB1ENR|=GPIOA_EN;

	GPIOA->MODER&=~(15U<<4);
	GPIOA->MODER|=(10U<<4);

	GPIOA->AFR[0]|=((7U<<8)|(7U<<12));

	USART2->CR1&=~(1U<<12);
	USART2->CR2&=~(3U<<12);

	USART2->CR3|=(1U<<7);

	setBaudRate(USART2,9600);

	USART2->CR1|=(1U<<3);

	USART2->CR1|=(1U<<13);

}


static void setBudRate(USART_TypeDef* USART,uint32_t baud)
{
	USART->BRR=((SYSCLK)/baud);
}
