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

static void setBaudRate(USART_TypeDef* USART,uint32_t baud);

void uart_init()
{
	RCC->APB1ENR|=USART2_EN;

	RCC->AHB1ENR|=GPIOA_EN;

	GPIOA->MODER&=~(15U<<4);
	GPIOA->MODER|=(10U<<4);

	GPIOA->AFR[0]|=((7U<<8)|(7U<<12));

	USART2->CR1&=~(1U<<12);
	USART2->CR2&=~(3U<<12);

	USART2->CR3|=(1U<<6);

	setBaudRate(USART2,9600);

	USART2->CR1|=((1U<<3)|(1U<<2));

	USART2->CR1|=(1U<<13);

}

void disable_gnss(uint8_t  *arr,uint8_t size)
{
	for(int i=0;i<size;i++)
	{
		while(!(USART2->SR & (1U<<7))){}
					USART2->DR=arr[i];
	}
}


static void setBaudRate(USART_TypeDef* USART,uint32_t baud)
{
	USART->BRR=((SYSCLK)/baud);
}
