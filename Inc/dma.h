/*
 * dma.h
 *
 *  Created on: Nov 21, 2026
 *      Author: LalinPrasadC
 */

#ifndef DMA_H_
#define DMA_H_

#include "stm32f401xc.h"

void dma_gps_receive(const char* data,uint8_t size);

void DMA1_Stream5_IRQHandler();

#endif /* DMA_H_ */
