#ifndef __LCD_H
#define __LCD_H		

///////////////////////////加入项目的关联头文件////////////////////////////////////

#include "main.h"
#include "stdlib.h"
#include "spi.h"
#include "font.h"
#include "Text.h"
//#include "Dis_Picture.h"

extern uint16_t D_Color; //点阵颜色
extern uint16_t B_Color; //背景颜色

//////////////////////////////////////////////////////////////////////////////////	 

//LCD液晶屏驱动程序

//********************************************************************************//

//数据类型定义

/* exact-width signed integer types */
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   __INT32_TYPE__ int32_t;
typedef   signed       long long int64_t;


/* exact-width unsigned integer types */
typedef unsigned          char   uint8_t;
typedef unsigned short     int   uint16_t;
typedef __UINT32_TYPE__   uint32_t;
typedef unsigned       long long uint64_t;


//typedef uint32_t  u32;
//typedef uint16_t u16;
//typedef uint8_t  u8;

//cubemx上选择SPI2单工模式
//#define LCD_CS          11       //片选CS引脚        PB11
//#define LCD_RS          10        //寄存器/数据选择DC引脚 PB10
//#define LCD_RST         12       //复位引脚RES        PB12
//#define LCD_BLK         8        //背光引脚           PA8

/****************************************************************************************************/
//LCD重要参数集
typedef struct  
{										    
	uint16_t width;			  //LCD 宽度
	uint16_t height;			  //LCD 高度
	uint16_t id;				  //LCD ID
	uint8_t  dir;			  //横屏还是竖屏控制：竖屏和横屏。
	uint16_t	wramcmd;		  //开始写gram指令
	uint16_t  setxcmd;		  //设置x坐标指令
	uint16_t  setycmd;		  //设置y坐标指令
}_lcd_dev; 	  



/////////////////////////////////////用户配置区///////////////////////////////////

//支持横竖屏快速定义切换

#define LCD_X  	            128     //横向点阵数量
#define LCD_H  	            160     //纵向

#define LCD_DIR_Mode  	    2	    //4种工作模式，0和1是竖屏模式，2和3是横屏模式
#define LCD_Picture  	    1	    //演示图片选择设置： 		0,竖屏图片   1,横屏图片

extern uint8_t USE_HORIZONTAL;      //方向设置： 		0,竖屏模式   1,横屏模式.

//引脚定义(已包含在main.h中）
#define GPIO_TYPE    GPIOB
#define LCD_CS          12       //片选CS引脚            PB12
#define LCD_RS          14       //寄存器/数据选择DC引脚  PB14
#define LCD_RST         11       //复位引脚RES           PB13
//#define LCD_BLK         11       //背光引脚              PB11

#define	LCD_CS_SET  	GPIO_TYPE->BSRR=1<<LCD_CS
#define LCD_RST_SET     GPIO_TYPE->BSRR=1<<LCD_RST
#define	LCD_RS_SET  	GPIO_TYPE->BSRR=1<<LCD_RS

#define	LCD_CS_CLR  	GPIO_TYPE->BRR=1<<LCD_CS
#define LCD_RST_CLR     GPIO_TYPE->BRR=1<<LCD_RST
#define	LCD_RS_CLR  	GPIO_TYPE->BRR=1<<LCD_RS

//#define	LCD_BLK_SET  	GPIOA->BSRR=1<<LCD_BLK
//#define	LCD_BLK_RESET  	GPIOA->BRR=1<<LCD_BLK
//////////////////////////////////////////////////////////////////////////////////	

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数

//LCD的画笔颜色和背景色

extern uint16_t  POINT_COLOR;//默认红色
extern uint16_t  BACK_COLOR; //背景颜色.默认为白色

//扫描方向定义--扫描方式有不同规格，可能定义不左右和上下的参照方向不同，总结方式，只有一下八种

#define L2R_U2D  0 //从左到右,从上到下
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上

#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左


///////////////////////////  颜色值  ///////////////////////////////////////////////////////

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F
#define BRED             0xF81F
#define GRED 			 0xFFE0
#define GBLUE			 0x07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0xBC40 //棕色
#define BRRED 			 0xFC07 //棕红色
#define GRAY  			 0x8430 //灰色


//GUI颜色

#define DARKBLUE      	 0x01CF	//深蓝色
#define LIGHTBLUE      	 0x7D7C	//浅蓝色
#define GRAYBLUE       	 0x5458 //灰蓝色
//以上三色为PANEL的颜色
 
 
#define LIGHTGREEN     	 0x841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 0xC618 //浅灰色(PANNEL),窗体背景色

#define GRAY0            0xEF7D   	    //灰色0
#define GRAY1            0x8410      	//灰色1
#define GRAY2            0x4208      	//灰色2

#define LGRAYBLUE        0xA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0x2B12 //浅棕蓝色(选择条目的反色)



////////////////////////硬件驱动-功能函数///////////////////////////////////////////////////////////////////////////////


void SPI2_Init(void);                //这里针是对SPI2的初始化
//void LCD_GPIO_Init(void);            //液晶IO初始化配置
uint8_t SPI2_ReadWriteByte(uint8_t TxData);    //SPI接口数据传输函数

void LCD_WR_REG(uint16_t regval);        //液晶屏--写寄存器函数
void LCD_WR_DATA8(uint8_t data);          //写8位数据
void LCD_WR_DATA16(uint16_t data);       //写16位数据


void LCD_Init(void);													   	              //初始化
void LCD_HardwareRest(void);                                    //硬复位--如果IO连接，硬件复位可控有效
void LCD_SoftRest(void);                                        //软复位
void LCD_DisplayOn(void);													              //开显示
void LCD_DisplayOff(void);													            //关显示


//////////////////以下函数是屏幕显示图形的简单驱动函数///////////////////////////////////////////////////////////////////////

void LCD_Clear(uint16_t Color);	 										                //清屏
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);									            //设置光标
void LCD_DrawPoint(uint16_t x,uint16_t y);											        //画点--使用设置的笔尖颜色
void LCD_Fast_DrawPoint(uint16_t x,uint16_t y,uint16_t color);								        //快速画点--使用当前输入颜色参数

void LCD_Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r, uint16_t Color);					            //画圆
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t Color);		                //画线
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t Color);                  //画矩形

void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color);		   			            //填充单色
void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color);		                //填充指定颜色
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint16_t color,uint8_t mode);			        //显示一个字符
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint16_t color);  		            //显示一个数字
void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint16_t color,uint8_t mode);	        //显示 数字
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint16_t color,uint8_t *p);		//显示一个字符串,12/16字体

void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);                                   //写寄存器

void LCD_WriteRAM_Prepare(void);                                                    //开始写GRAM  命令
void LCD_WriteRAM(uint16_t RGB_Code);		                                            //LCD写GRAM

void LCD_Display_Dir(uint8_t dir);						                                //设置屏幕显示方向
void LCD_Set_Window(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height);                            //设置窗口

void Draw_Test(void);                                                               //绘图工具函数测试
void Color_Test(void);                                                              //颜色填充显示测试
void Font_Test(void);                                                               //字体字形显示测试
void GBK_LibFont_Test(void);                                                        //GBK字体字形显示测试
void Demo_Menu(void);                                                               //演示程序菜单



#endif  
