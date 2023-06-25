#include "stm32g431xx.h"
#include "sys.h"
#include "led.h"

int main(void)
{
	SYSCLK_170MHz();
	led_init();
	while(1)
	{
		GPIOB->ODR&=0x0<<11;
	}
	
}

