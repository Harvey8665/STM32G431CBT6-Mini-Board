#include "sys.h"

//SYSCLK_170MHz V1.0 2023/6/20
uint16_t SYSCLK_170MHz(void)
{
	#if HSE1  //外部晶振为25MHz
	uint16_t temp = 0x2000;
	RCC->CR |= RCC_CR_HSEON;
	while((!(RCC->CR & RCC_CR_HSERDY))&&(--temp));//等待HSE就绪
	if(!temp)
	{
		return FAILED;
	}
	RCC->CR &= ~RCC_CR_PLLON;
	temp = 0x2000;
	while((RCC->CR & RCC_CR_PLLRDY) && (--temp));//等待PLL下线
	if(!temp)
	{
		return FAILED;
	}
	RCC->CFGR = RCC_CFGR_PPRE2_DIV1|RCC_CFGR_PPRE1_DIV1|RCC_CFGR_HPRE_DIV1|RCC_CFGR_SW_HSI;  //APB2不分频，APB1不分频，AHB不分频，HSI作为系统时钟
	temp = 0x2000;
	while(--temp);//等待AHB稳定
	//RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
	PWR->CR5 &= ~PWR_CR5_R1MODE;//设置为range1_boost
	FLASH->ACR &= ~FLASH_ACR_LATENCY;
	FLASH->ACR |= FLASH_ACR_LATENCY_4WS;
	temp = 0x2000;
	while(--temp);//等待系统稳定
	RCC->PLLCFGR = (68<<RCC_PLLCFGR_PLLN_Pos)|(4<<RCC_PLLCFGR_PLLM_Pos)|RCC_PLLCFGR_PLLSRC_HSE;//(25/5)*68= 340 MHz，HSE作为系统时钟
	RCC->CR |= RCC_CR_PLLON;
	temp = 0xf000;
	while((!(RCC->CR & RCC_CR_PLLRDY)) && (--temp));//等待PLL准备就绪
	if(!temp)
	{
		return FAILED;
	}
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN;  //340/2=170 MHz
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	temp = 0xf000;
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS);//等待系统设置PLL主时钟完成标志位置位
	if(temp)
	{
		temp = 0;
		while(--temp);//等待系统稳定
		RCC->CFGR &= ~RCC_CFGR_HPRE;//AHB 不分频 == SYSCLK
		return SUCCEED;
	}
	else
	{
		return FAILED;
	}
	#endif
}


