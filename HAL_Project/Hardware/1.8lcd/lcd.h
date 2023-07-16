#ifndef __LCD_H
#define __LCD_H		

///////////////////////////������Ŀ�Ĺ���ͷ�ļ�////////////////////////////////////

#include "main.h"
#include "stdlib.h"
#include "spi.h"
#include "font.h"
#include "Text.h"
//#include "Dis_Picture.h"

extern uint16_t D_Color; //������ɫ
extern uint16_t B_Color; //������ɫ

//////////////////////////////////////////////////////////////////////////////////	 

//LCDҺ������������

//********************************************************************************//

//�������Ͷ���

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

//cubemx��ѡ��SPI2����ģʽ
//#define LCD_CS          11       //ƬѡCS����        PB11
//#define LCD_RS          10        //�Ĵ���/����ѡ��DC���� PB10
//#define LCD_RST         12       //��λ����RES        PB12
//#define LCD_BLK         8        //��������           PA8

/****************************************************************************************************/
//LCD��Ҫ������
typedef struct  
{										    
	uint16_t width;			  //LCD ���
	uint16_t height;			  //LCD �߶�
	uint16_t id;				  //LCD ID
	uint8_t  dir;			  //���������������ƣ������ͺ�����
	uint16_t	wramcmd;		  //��ʼдgramָ��
	uint16_t  setxcmd;		  //����x����ָ��
	uint16_t  setycmd;		  //����y����ָ��
}_lcd_dev; 	  



/////////////////////////////////////�û�������///////////////////////////////////

//֧�ֺ��������ٶ����л�

#define LCD_X  	            128     //�����������
#define LCD_H  	            160     //����

#define LCD_DIR_Mode  	    2	    //4�ֹ���ģʽ��0��1������ģʽ��2��3�Ǻ���ģʽ
#define LCD_Picture  	    1	    //��ʾͼƬѡ�����ã� 		0,����ͼƬ   1,����ͼƬ

extern uint8_t USE_HORIZONTAL;      //�������ã� 		0,����ģʽ   1,����ģʽ.

//���Ŷ���(�Ѱ�����main.h�У�
#define GPIO_TYPE    GPIOB
#define LCD_CS          12       //ƬѡCS����            PB12
#define LCD_RS          14       //�Ĵ���/����ѡ��DC����  PB14
#define LCD_RST         11       //��λ����RES           PB13
//#define LCD_BLK         11       //��������              PB11

#define	LCD_CS_SET  	GPIO_TYPE->BSRR=1<<LCD_CS
#define LCD_RST_SET     GPIO_TYPE->BSRR=1<<LCD_RST
#define	LCD_RS_SET  	GPIO_TYPE->BSRR=1<<LCD_RS

#define	LCD_CS_CLR  	GPIO_TYPE->BRR=1<<LCD_CS
#define LCD_RST_CLR     GPIO_TYPE->BRR=1<<LCD_RST
#define	LCD_RS_CLR  	GPIO_TYPE->BRR=1<<LCD_RS

//#define	LCD_BLK_SET  	GPIOA->BSRR=1<<LCD_BLK
//#define	LCD_BLK_RESET  	GPIOA->BRR=1<<LCD_BLK
//////////////////////////////////////////////////////////////////////////////////	

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����

//LCD�Ļ�����ɫ�ͱ���ɫ

extern uint16_t  POINT_COLOR;//Ĭ�Ϻ�ɫ
extern uint16_t  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

//ɨ�跽����--ɨ�跽ʽ�в�ͬ��񣬿��ܶ��岻���Һ����µĲ��շ���ͬ���᷽ܽʽ��ֻ��һ�°���

#define L2R_U2D  0 //������,���ϵ���
#define L2R_D2U  1 //������,���µ���
#define R2L_U2D  2 //���ҵ���,���ϵ���
#define R2L_D2U  3 //���ҵ���,���µ���

#define U2D_L2R  4 //���ϵ���,������
#define U2D_R2L  5 //���ϵ���,���ҵ���
#define D2U_L2R  6 //���µ���,������
#define D2U_R2L  7 //���µ���,���ҵ���


///////////////////////////  ��ɫֵ  ///////////////////////////////////////////////////////

//������ɫ
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
#define BROWN 			 0xBC40 //��ɫ
#define BRRED 			 0xFC07 //�غ�ɫ
#define GRAY  			 0x8430 //��ɫ


//GUI��ɫ

#define DARKBLUE      	 0x01CF	//����ɫ
#define LIGHTBLUE      	 0x7D7C	//ǳ��ɫ
#define GRAYBLUE       	 0x5458 //����ɫ
//������ɫΪPANEL����ɫ
 
 
#define LIGHTGREEN     	 0x841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 0xC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define GRAY0            0xEF7D   	    //��ɫ0
#define GRAY1            0x8410      	//��ɫ1
#define GRAY2            0x4208      	//��ɫ2

#define LGRAYBLUE        0xA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0x2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)



////////////////////////Ӳ������-���ܺ���///////////////////////////////////////////////////////////////////////////////


void SPI2_Init(void);                //�������Ƕ�SPI2�ĳ�ʼ��
//void LCD_GPIO_Init(void);            //Һ��IO��ʼ������
uint8_t SPI2_ReadWriteByte(uint8_t TxData);    //SPI�ӿ����ݴ��亯��

void LCD_WR_REG(uint16_t regval);        //Һ����--д�Ĵ�������
void LCD_WR_DATA8(uint8_t data);          //д8λ����
void LCD_WR_DATA16(uint16_t data);       //д16λ����


void LCD_Init(void);													   	              //��ʼ��
void LCD_HardwareRest(void);                                    //Ӳ��λ--���IO���ӣ�Ӳ����λ�ɿ���Ч
void LCD_SoftRest(void);                                        //��λ
void LCD_DisplayOn(void);													              //����ʾ
void LCD_DisplayOff(void);													            //����ʾ


//////////////////���º�������Ļ��ʾͼ�εļ���������///////////////////////////////////////////////////////////////////////

void LCD_Clear(uint16_t Color);	 										                //����
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);									            //���ù��
void LCD_DrawPoint(uint16_t x,uint16_t y);											        //����--ʹ�����õıʼ���ɫ
void LCD_Fast_DrawPoint(uint16_t x,uint16_t y,uint16_t color);								        //���ٻ���--ʹ�õ�ǰ������ɫ����

void LCD_Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r, uint16_t Color);					            //��Բ
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t Color);		                //����
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t Color);                  //������

void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color);		   			            //��䵥ɫ
void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color);		                //���ָ����ɫ
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint16_t color,uint8_t mode);			        //��ʾһ���ַ�
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint16_t color);  		            //��ʾһ������
void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint16_t color,uint8_t mode);	        //��ʾ ����
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint16_t color,uint8_t *p);		//��ʾһ���ַ���,12/16����

void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);                                   //д�Ĵ���

void LCD_WriteRAM_Prepare(void);                                                    //��ʼдGRAM  ����
void LCD_WriteRAM(uint16_t RGB_Code);		                                            //LCDдGRAM

void LCD_Display_Dir(uint8_t dir);						                                //������Ļ��ʾ����
void LCD_Set_Window(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height);                            //���ô���

void Draw_Test(void);                                                               //��ͼ���ߺ�������
void Color_Test(void);                                                              //��ɫ�����ʾ����
void Font_Test(void);                                                               //����������ʾ����
void GBK_LibFont_Test(void);                                                        //GBK����������ʾ����
void Demo_Menu(void);                                                               //��ʾ����˵�



#endif  
