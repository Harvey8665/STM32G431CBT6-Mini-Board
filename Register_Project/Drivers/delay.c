#include "delay.h"


static uint32_t  fac_us=0;					//us延时倍乘数

void delay_init(void)
{
	SysTick->CTRL|=(1<<2);                  //SYSTICK使用FCLK（170MHz）
	fac_us=170;      				        //分频，频率为170MHz/170=1MHz，即SysTick中断一次延时1us
}

//Harvey 2023/07/07 V1.0
//delay_us 微秒级延时函数
//精度：在100us以下会有误差，随着延时时间越短，误差越大，1us时误差约为+0.24~0.27us
//nus最大值：98689us=98.689ms
void delay_us(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us; 				//时间加载	  		 
	SysTick->VAL=0x00;        				//清空计数器
	SysTick->CTRL|=1<<0;      				//开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL&=~(1<<0);      	 		//关闭计数器
	SysTick->VAL =0X00;       				//清空计数器 
}

//Harvey 2023/07/07 V1.0
//delay_ms 毫秒级延时函数
//精度：未知，测试定时10s的误差为±0.01s以内，定时20s的误差为±0.15s
//nms理论最大值：2147483ms=2147.483s（建议取值不要超过20000ms，即20s，否则精度大大降低）
void delay_ms(uint32_t nms)
{
	uint32_t yu,bei,i;
	bei=(uint32_t)(nms*1000)/90000;          //计算需要调用多少次延时90ms
	yu=nms*1000-bei*90000;                   //计算除了bei个90ms个延时之外再需要延时yu个us
	for(i=0;i<bei;i++)                       //循环调用bei次延时90ms
		delay_us(90000);
	delay_us(yu);                            //延时剩下的yu个us
}

//Harvey 2023/07/07 V1.0
//delay_s 秒级延时函数
//ns理论最大值：2147s（建议取值不要超过20s，避免误差过大）
void delay_s(uint32_t ns)
{
	delay_ms(ns*1000);
}

