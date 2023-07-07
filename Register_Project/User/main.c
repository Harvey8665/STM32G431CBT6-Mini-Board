#include "stm32g431xx.h"
#include "sys.h"
#include "led.h"
#include "delay.h"

int main(void)
{
	SYSCLK_170MHz();
	led_init();
	delay_init();
	while(1)
	{
		GPIOB->ODR&=0<<11;
		delay_ms(500);
		GPIOB->ODR|=1<<11;
		delay_ms(500);
	}
	
}

