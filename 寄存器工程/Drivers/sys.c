#include "sys.h"

//SYSCLK_170MHz V1.0 2023/6/20
uint16_t SYSCLK_170MHz(void)
{
	#if HSE1  //�ⲿ����Ϊ25MHz
	uint16_t temp = 0x2000;
	RCC->CR |= RCC_CR_HSEON;
	while((!(RCC->CR & RCC_CR_HSERDY))&&(--temp));//�ȴ�HSE����
	if(!temp)
	{
		return FAILED;
	}
	RCC->CR &= ~RCC_CR_PLLON;
	temp = 0x2000;
	while((RCC->CR & RCC_CR_PLLRDY) && (--temp));//�ȴ�PLL����
	if(!temp)
	{
		return FAILED;
	}
	RCC->CFGR = RCC_CFGR_PPRE2_DIV1|RCC_CFGR_PPRE1_DIV1|RCC_CFGR_HPRE_DIV1|RCC_CFGR_SW_HSI;  //APB2����Ƶ��APB1����Ƶ��AHB����Ƶ��HSI��Ϊϵͳʱ��
	temp = 0x2000;
	while(--temp);//�ȴ�AHB�ȶ�
	//RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
	PWR->CR5 &= ~PWR_CR5_R1MODE;//����Ϊrange1_boost
	FLASH->ACR &= ~FLASH_ACR_LATENCY;
	FLASH->ACR |= FLASH_ACR_LATENCY_4WS;
	temp = 0x2000;
	while(--temp);//�ȴ�ϵͳ�ȶ�
	RCC->PLLCFGR = (68<<RCC_PLLCFGR_PLLN_Pos)|(4<<RCC_PLLCFGR_PLLM_Pos)|RCC_PLLCFGR_PLLSRC_HSE;//(25/5)*68= 340 MHz��HSE��Ϊϵͳʱ��
	RCC->CR |= RCC_CR_PLLON;
	temp = 0xf000;
	while((!(RCC->CR & RCC_CR_PLLRDY)) && (--temp));//�ȴ�PLL׼������
	if(!temp)
	{
		return FAILED;
	}
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN;  //340/2=170 MHz
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	temp = 0xf000;
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS);//�ȴ�ϵͳ����PLL��ʱ����ɱ�־λ��λ
	if(temp)
	{
		temp = 0;
		while(--temp);//�ȴ�ϵͳ�ȶ�
		RCC->CFGR &= ~RCC_CFGR_HPRE;//AHB ����Ƶ == SYSCLK
		return SUCCEED;
	}
	else
	{
		return FAILED;
	}
	#endif
}


