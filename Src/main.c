#include <timer.h>
#include <dma.h>
#include <interrupt.h>
#include <uart.h>
#include <ubox.h>
#include <gnss.h>

int main(void)
{
	setClock84();
	gnssInterrupt();
	uart_init();

    RCC->AHB1ENR |= (1U << 2);

    GPIOC->MODER &= ~(3U << 26);
    GPIOC->MODER |=  (1U << 26);


    char data[149];

	dma_gps_receive(data,149);
	delay(200);
	disable_gnss(disable_gll,11);
	delay(200);
	disable_gnss(disable_gsa,sizeof(disable_gsa));
	delay(200);
	disable_gnss(disable_gsv,sizeof(disable_gsv));
	delay(200);
	disable_gnss(disable_vtg,sizeof(disable_vtg));
	delay(200);



    while (1)
    {
        GPIOC->ODR &= ~(1U << 13);  // LED ON
        delay(2000);

        GPIOC->ODR |= (1U << 13);   // LED OFF
        delay(2000);
    }
}
