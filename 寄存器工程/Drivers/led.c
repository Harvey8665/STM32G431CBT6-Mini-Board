#include "led.h"

//LED0: PB11
//LED引脚初始化函数
//led_init V1.0 2023/6/20
void led_init(void)
{
	RCC->AHB2ENR&=~(1<<1);      //清除原来的设置
	RCC->AHB2ENR|=1<<1;         //使能 PORTB 口时钟
	GPIOE->MODER&=~(0x3<<22);
	GPIOE->MODER|=0x1<<22;      //初始化PB11为输出模式
	GPIOE->OTYPER&=~(0x1<<11);  //PB11输出推挽
	GPIOE->OSPEEDR&=~(0x3<<22);
	GPIOE->OSPEEDR|=0x2<<22;    //PB11高速模式
	GPIOE->PUPDR&=~(0x3<<22);
	GPIOE->PUPDR|=0x1<<22;      //PB11上拉
	GPIOE->ODR&=~(0x1<<11);
	GPIOE->ODR|=0x1<<11;        //PB11输出1（高电平）
}





