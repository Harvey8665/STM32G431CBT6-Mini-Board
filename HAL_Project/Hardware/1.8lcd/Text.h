#ifndef __Text_H__
#define __Text_H__	 

#include "main.h"
#include "font.h"
#include "Text.h"
#include "string.h"

//////////////////////////////////////////////////////////////////////////////////	 

/******************************************************************************/		 

void Copy_Mem (unsigned char *P1, const unsigned char *P2,unsigned int Count);  //内部存储-拷贝函数
void Copy_HZK16(uint8_t *Dot, uint8_t num, uint8_t Q, uint8_t W);   //根据区位码和字号，获取对应的点阵(16*16)
void Copy_HZK24(uint8_t *Dot, uint8_t num, uint8_t Q, uint8_t W);   //根据区位码和字号，获取对应的点阵(24*24)
void Get_HzMat(uint8_t *code,uint8_t *mat,uint8_t size,uint8_t Font);			//根据区位码和字号，获取对应的点阵
void Show_Font(uint16_t x,uint16_t y,uint8_t *font,uint8_t size,uint16_t color,uint8_t mode);					//显示一个指定大小的汉字
void Show_Str(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t*str,uint8_t size, uint16_t color, uint8_t mode);	//在指定位置开始显示一个字符串，支持自动换行
void Draw_Font16B(uint16_t x,uint16_t y, uint16_t color, uint8_t*str);//在指定位置开始显示一个16x16点阵的--字符串，支持自动换行(至屏幕一行的终点后，自动换到下一个x起点位置)
void Draw_Font24B(uint16_t x,uint16_t y, uint16_t color, uint8_t*str);//在指定位置开始显示一个24x24点阵的--字符串，支持自动换行(至屏幕一行的终点后，自动换到下一个x起点位置)


#endif
