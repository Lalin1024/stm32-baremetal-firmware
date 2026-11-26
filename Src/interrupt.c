/*
 * interupt.c
 *
 *  Created on: Nov 24, 2026
 *      Author: lalin
 */

#include <interrupt.h>

void gnssInterrupt()
{
	NVIC_EnableIRQ(DMA1_Stream5_IRQn);
}
