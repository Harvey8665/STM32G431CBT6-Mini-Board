#ifndef __DELAY_H
#define __DELAY_H
//Harvey 2023/07/07 V1.0
//����SysTick��ʱ������ʱ����
#include "stm32g431xx.h"

void delay_init(void);            //��ʱ������ʼ��
void delay_ms(uint32_t nms);      //������ʱ����
void delay_us(uint32_t nus);      //΢����ʱ����
void delay_s(uint32_t ns);        //����ʱ����

#endif

