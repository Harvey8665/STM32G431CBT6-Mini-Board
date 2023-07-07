#ifndef __DELAY_H
#define __DELAY_H
//Harvey 2023/07/07 V1.0
//采用SysTick定时器的延时函数
#include "stm32g431xx.h"

void delay_init(void);            //延时函数初始化
void delay_ms(uint32_t nms);      //毫秒延时函数
void delay_us(uint32_t nus);      //微秒延时函数
void delay_s(uint32_t ns);        //秒延时函数

#endif

