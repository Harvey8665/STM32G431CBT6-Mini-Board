#include "led.h"

//LED0: PB11
//LED���ų�ʼ������
//led_init V1.0 2023/6/20
void led_init(void)
{
	RCC->AHB2ENR&=~(1<<1);      //���ԭ��������
	RCC->AHB2ENR|=1<<1;         //ʹ�� PORTB ��ʱ��
	GPIOB->MODER&=~(0x3<<22);
	GPIOB->MODER|=0x1<<22;      //��ʼ��PB11Ϊ���ģʽ
	GPIOB->OTYPER&=~(0x1<<11);  //PB11�������
	GPIOB->OSPEEDR&=~(0x3<<22);
	GPIOB->OSPEEDR|=0x2<<22;    //PB11����ģʽ
	GPIOB->PUPDR&=~(0x3<<22);
	GPIOB->PUPDR|=0x1<<22;      //PB11����
	GPIOB->ODR&=~(0x1<<11);
	GPIOB->ODR|=0x1<<11;        //PB11���1���ߵ�ƽ��
}





