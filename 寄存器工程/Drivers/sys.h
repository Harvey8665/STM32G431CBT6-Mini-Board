#ifndef __SYS_H
#define __SYS_H


#include "stm32g431xx.h"

typedef enum
{
	SUCCEED =0x00U,
	FAILED  =0x01U,
	BUSY    =0x02U,
	TIMEOUT =0x03U
}StatusTypeDef;

typedef enum
{
	UNLOCKED = 0x00U,
    LOCKED   = 0x01U
}LockTypeDef;

void SystemInit(void);

#endif

