/*
 * timer.c
 *
 *  Created on: Nov 8, 2026
 *      Author: lalin
 */
#include <timer.h>


void setClock_16()
{
	RCC->CR=0;

	RCC->CR|=(1U<<0);

	while(!(RCC->CR & (1U<<1)))
	{

	}

	RCC->CFGR&=~(3U<<0);
	while((RCC->CFGR & (~(3U<<2)))){}
}

void setClock84()
{
    // -----------------------------------------
    // STEP 1: Switch to HSI (16 MHz)
    // -----------------------------------------
    setClock_16();


    // -----------------------------------------
    // STEP 2: Configure PWR Voltage Scaling
    // -----------------------------------------

    // Enable PWR peripheral clock
    RCC->APB1ENR |= (1U << 28);

    // Select Voltage Scale 2
    PWR->CR &= ~(3U << 14);
    PWR->CR |=  (2U << 14);


    // -----------------------------------------
    // STEP 3: Configure Flash latency
    // -----------------------------------------

    // Clear LATENCY bits [2:0]
    FLASH->ACR &= ~(7U << 0);

    // Set 2 wait states
    FLASH->ACR |= (2U << 0);


    // -----------------------------------------
    // STEP 4: Configure bus prescalers
    // -----------------------------------------

    // AHB prescaler = /1
    RCC->CFGR &= ~(15U << 4);

    // APB1 prescaler = /2
    RCC->CFGR &= ~(7U << 10);
    RCC->CFGR |=  (4U << 10);

    // APB2 prescaler = /1
    RCC->CFGR &= ~(7U << 13);


    // -----------------------------------------
    // STEP 5: Disable PLL
    // -----------------------------------------

    RCC->CR &= ~(1U << 24);

    // Wait until PLL is disabled
    while (RCC->CR & (1U << 25)) {}


    // -----------------------------------------
    // STEP 6: Configure PLL
    // -----------------------------------------

    RCC->PLLCFGR = 0;

    // PLLM = 8
    RCC->PLLCFGR |= (8U << 0);

    // PLLN = 168
    RCC->PLLCFGR |= (168U << 6);

    // PLLP = 4 (encoding 01)
    RCC->PLLCFGR |= (1U << 16);

    // PLLQ = 7
    RCC->PLLCFGR |= (7U << 24);

    // PLLSRC = 0 -> HSI selected


    // -----------------------------------------
    // STEP 7: Enable PLL
    // -----------------------------------------

    RCC->CR |= (1U << 24);

    // Wait until PLL is ready
    while (!(RCC->CR & (1U << 25))) {}


    // -----------------------------------------
    // STEP 8: Select PLL as SYSCLK
    // -----------------------------------------

    // SW = 10 -> PLL selected
    RCC->CFGR &= ~(3U << 0);
    RCC->CFGR |=  (2U << 0);

    // Wait until SWS = 10 -> PLL confirmed
    while ((RCC->CFGR & (3U << 2)) != (2U << 2)) {}


}


void delay(uint32_t val)
{
	RCC->APB1ENR|=(1U<<1);

	TIM3->PSC=8399;
	TIM3->ARR=((val*10U)-1);

	TIM3->CNT=0;

	TIM3->EGR=(1U<<0);

	TIM3->CR1|=(1U<<0);

	TIM3->SR &= ~(1U << 0);

	while(!(TIM3->SR & (1U<<0)));

}
