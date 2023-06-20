#include "led.h"

//LED0: PB11
//LED引脚初始化函数
//led_init V1.0 2023/6/20
void led_init(void)
{
	RCC->AHB2ENR&=~(1<<1);      //清除原来的设置
	RCC->AHB2ENR|=1<<1;         //使能 PORTB 口时钟
	GPIOB->MODER&=~(0x3<<22);
	GPIOB->MODER|=0x1<<22;      //初始化PB11为输出模式
	GPIOB->OTYPER&=~(0x1<<11);  //PB11输出推挽
	GPIOB->OSPEEDR&=~(0x3<<22);
	GPIOB->OSPEEDR|=0x2<<22;    //PB11高速模式
	GPIOB->PUPDR&=~(0x3<<22);
	GPIOB->PUPDR|=0x1<<22;      //PB11上拉
	GPIOB->ODR&=~(0x1<<11);
	GPIOB->ODR|=0x1<<11;        //PB11输出1（高电平）
}





