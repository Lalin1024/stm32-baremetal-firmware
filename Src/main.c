#include<timer.h>

int main(void)
{
	setClock84();
    RCC->AHB1ENR |= (1U << 2);

    GPIOC->MODER &= ~(3U << 26);
    GPIOC->MODER |=  (1U << 26);

    while (1)
    {
        GPIOC->ODR &= ~(1U << 13);  // LED ON
        delay(2000);

        GPIOC->ODR |= (1U << 13);   // LED OFF
        delay(2000);
    }
}
