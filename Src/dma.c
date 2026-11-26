/*
 * dma.c
 *
 *  Created on: Nov 22, 2026
 *      Author: lalin
 */

#include "dma.h"

#define DMA1_EN	(1U<<21)

void dma_gps_receive(const char* data,uint8_t size)
{
	RCC->AHB1ENR|=DMA1_EN;

	DMA1_Stream5->CR&=~(1U<<0);

	while(DMA1_Stream5->CR & (1U<<0)){}

	DMA1_Stream5->PAR=(uint32_t)&(USART2->DR);

	DMA1_Stream5->M0AR=(uint32_t) data;

	DMA1_Stream5->NDTR=size;

	DMA1_Stream5->CR &= ~(7U << 25);
	DMA1_Stream5->CR |=  (4U << 25);

	DMA1_Stream5->CR&=~(3U<<16);
	DMA1_Stream5->CR|=(1U<<17);

	DMA1_Stream5->FCR=0;

	DMA1_Stream5->CR&=~(3u<<6);

	DMA1_Stream5->CR|=(1U<<8);

	DMA1_Stream5->CR&=~(1u<<9);

	DMA1_Stream5->CR|=(1u<<10);

	DMA1_Stream5->CR&=~(3u<<11);

	DMA1_Stream5->CR|=(1U<<4);

	DMA1_Stream5->CR|=(1U<<0);

}


void DMA1_Stream5_IRQHandler()
{
	if(DMA1->HISR & (1U<<11))
	{
		DMA1->HIFCR|=(1U<<11);
	}
}
