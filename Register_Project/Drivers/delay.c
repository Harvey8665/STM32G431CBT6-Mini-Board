#include "delay.h"


static uint32_t  fac_us=0;					//us��ʱ������

void delay_init(void)
{
	SysTick->CTRL|=(1<<2);                  //SYSTICKʹ��FCLK��170MHz��
	fac_us=170;      				        //��Ƶ��Ƶ��Ϊ170MHz/170=1MHz����SysTick�ж�һ����ʱ1us
}

//Harvey 2023/07/07 V1.0
//delay_us ΢�뼶��ʱ����
//���ȣ���100us���»�����������ʱʱ��Խ�̣����Խ��1usʱ���ԼΪ+0.24~0.27us
//nus���ֵ��98689us=98.689ms
void delay_us(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us; 				//ʱ�����	  		 
	SysTick->VAL=0x00;        				//��ռ�����
	SysTick->CTRL|=1<<0;      				//��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~(1<<0);      	 		//�رռ�����
	SysTick->VAL =0X00;       				//��ռ����� 
}

//Harvey 2023/07/07 V1.0
//delay_ms ���뼶��ʱ����
//���ȣ�δ֪�����Զ�ʱ10s�����Ϊ��0.01s���ڣ���ʱ20s�����Ϊ��0.15s
//nms�������ֵ��2147483ms=2147.483s������ȡֵ��Ҫ����20000ms����20s�����򾫶ȴ�󽵵ͣ�
void delay_ms(uint32_t nms)
{
	uint32_t yu,bei,i;
	bei=(uint32_t)(nms*1000)/90000;          //������Ҫ���ö��ٴ���ʱ90ms
	yu=nms*1000-bei*90000;                   //�������bei��90ms����ʱ֮������Ҫ��ʱyu��us
	for(i=0;i<bei;i++)                       //ѭ������bei����ʱ90ms
		delay_us(90000);
	delay_us(yu);                            //��ʱʣ�µ�yu��us
}

//Harvey 2023/07/07 V1.0
//delay_s �뼶��ʱ����
//ns�������ֵ��2147s������ȡֵ��Ҫ����20s������������
void delay_s(uint32_t ns)
{
	delay_ms(ns*1000);
}

