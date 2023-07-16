#include "lcd.h"


//////////////////////////////////////////////////////////////////////////////////	 

//1.8寸  LCD 液晶驱动	  芯片：ST7735s

//********************************************************************************

//////////////////////////////////////////////////////////////////////////////////	 
				 
//LCD的画笔颜色和背景色

uint16_t POINT_COLOR=0x0000;	//画笔颜色
uint16_t BACK_COLOR=0xFFFF;  //背景色

uint8_t USE_HORIZONTAL=0;    //方向设置： 		0,竖屏模式   1,横屏模式.


//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;


//本驱动程序使用的是MCU硬件SPI接口驱动


/******************************************************************************

  接口定义，请根据接线修改并修改相应IO初始化--驱动板子和IO要对应

	#define LCD_SDA        	//PB15      //数据输入线
	#define LCD_SCL        	//PB13      //时钟线
	#define LCD_CS        	//PB12      //片选
	#define LCD_SDO/RST     //PB14      //数据输出/复位	RES
	#define LCD_RS         	//PC5       //命令/数据切换DC
	#define LCD_BLK         //PB1    	  //背光控制


*******************************************************************************/


/******************************************************************************/

//函数： void SPI2_Init(void)

//函数功能：以下是 硬件SPI模块的初始化代码，配置成主机模式
//SPI口初始化
//这里针是对SPI2的初始化
/******************************************************************************/


void SPI2_Init(void)
{

    MX_SPI2_Init();
	SPI2_ReadWriteByte(0xff);//启动传输
	
}



/******************************************************************************/

//函数： void LCD_GPIO_Init(void)

//函数功能：驱动液晶IO初始化配置

//	#define LCD_SDA        	//PB15      //数据输入线
//	#define LCD_SCL        	//PB13      //时钟线
//	#define LCD_CS        	//PB12      //片选
//	#define LCD_SDO/RST     //PB14      //数据输出/复位RES
//	#define LCD_RS         	//PB1       //命令/数据切换DC
//	#define LCD_BLK         //PA8    	  //背光控制BL

/******************************************************************************/
//void LCD_GPIO_Init(void)
//{

//    GPIO_InitTypeDef GPIO_InitStruct = {0};

//    __HAL_RCC_GPIOD_CLK_ENABLE();
//    __HAL_RCC_GPIOB_CLK_ENABLE();
//    __HAL_RCC_GPIOA_CLK_ENABLE();

//    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//    GPIO_InitStruct.Pin = GPIO_PIN_8;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);



//    SPI2_Init();           //初始化硬件SPI2

////  LCD_HardwareRest();   //硬复位--如果IO连接，硬件复位可控有效

//}


/********************************************************************/
//函数：u8 SPI2_ReadWriteByte(u8 TxData)
//函数功能： SPI读写函数 ： 使用操作寄存器方式，速度更快

//SPI1 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
//*******************************************************************/

uint8_t SPI2_ReadWriteByte(uint8_t TxData)
{

    HAL_SPI_Transmit(&hspi2,&TxData, sizeof(TxData) ,HAL_MAX_DELAY);                                //返回通过SPIx最近接收的数据

}




//********************************************************************/

//函数：void LCD_WR_REG(u16 regval)
//函数功能：
//写寄存器函数
//regval:寄存器值
//*******************************************************************/

void LCD_WR_REG(uint16_t regval)
{
     LCD_CS_CLR;//LCD_CS=0  //片选
     LCD_RS_CLR;  //LCD_RS=0  //设置命令状态
	 SPI2_ReadWriteByte(regval&0x00FF);
     LCD_CS_SET;  //LCD_CS=1
}



//*******************************************************************/

//函数：void LCD_WR_DATA8(u8 data)   //写8位数据
//函数功能：
//液晶屏--写8位数据函数
//*******************************************************************/


void LCD_WR_DATA8(uint8_t data)   //写8位数据
{
    LCD_CS_CLR;  //LCD_CS=0  //片选
    LCD_RS_SET;	 //LCD_RS=1   //设置数据状态
	SPI2_ReadWriteByte(data);
    LCD_CS_SET;  //LCD_CS=1
}


//*******************************************************************/
//函数：void LCD_WR_DATA16(u16 data)   //写16位数据
//函数功能：写LCD数据
//输入参数：
//data:要写入的值
//*******************************************************************/


void LCD_WR_DATA16(uint16_t data)
{

    LCD_CS_CLR;  //LCD_CS=0  //片选
    LCD_RS_SET;	 //LCD_RS=1   //设置数据状态
	SPI2_ReadWriteByte(data>>8);
	SPI2_ReadWriteByte(data);
    LCD_CS_SET;    //LCD_CS=1
	
}


//*******************************************************************/

//函数：void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue)  //写液晶屏寄存器

//函数功能：写寄存器

//输入参数:
//LCD_Reg:寄存器地址
//LCD_RegValue:要写入的数据
//*******************************************************************/

void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg);		   //写入要写的寄存器序号
	LCD_WR_DATA8(LCD_RegValue);//写入数据
}


//*******************************************************************/
//函数：void LCD_WriteRAM_Prepare(void)
//函数功能：开始写GRAM  命令
//*******************************************************************/

void LCD_WriteRAM_Prepare(void)
{
 	LCD_WR_REG(lcddev.wramcmd);	  
}	



//*******************************************************************/
//函数：LCD_WriteRAM(u16 RGB_Code)
//函数功能：写入点阵颜色值
//输入参数:
//RGB_Code:颜色值
//*******************************************************************/

void LCD_WriteRAM(uint16_t RGB_Code)
{							    
	LCD_WR_DATA16( RGB_Code );//写十六位GRAM
}





//********************************************************************************/
//函数：void LCD_DisplayOn(void)
//函数功能：
//LCD开启显示
//*******************************************************************/
void LCD_DisplayOn(void)
{					   
	LCD_WR_REG(0X29);	//开启显示
}	


//*******************************************************************/
//函数：void LCD_DisplayOff(void)
//函数功能：
//LCD关闭显示
//*******************************************************************/

void LCD_DisplayOff(void)
{	   
	LCD_WR_REG(0X28);	//关闭显示

} 

//********************************************************************************/
//函数：void LCD_SoftRest(void)
//函数功能：给屏幕发命令，执行软复位命令
//LCD开启显示
//*******************************************************************/
void LCD_SoftRest(void)
{					   
//	LCD_WR_REG(0x01);	//发送软复位命令
	LCD_RST_CLR;
	HAL_Delay(100);
	LCD_RST_SET;
	HAL_Delay(50);      // delay 50 ms
}	


//********************************************************************************/
//函数：void LCD_SoftRest(void)
//函数功能：给屏幕发命令，执行软复位命令
//LCD开启显示
//*******************************************************************/
void LCD_HardwareRest(void)
{
    LCD_RS_CLR;     //液晶屏复位 --硬复位--使能       //PB14作为液晶屏复位控制引脚
	HAL_Delay(50);      // delay 50 ms
    LCD_RS_SET; //液晶屏复位 --硬复位--失能       //PB14作为液晶屏复位控制引脚
	HAL_Delay(30);      // delay 30 ms
}	



//*******************************************************************/
//函数：void LCD_SetCursor(u16 Xpos, u16 Ypos)
//函数功能：设置光标位置
//输入参数：
//Xpos:横坐标
//Ypos:纵坐标
//*******************************************************************/
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{	 
		if(USE_HORIZONTAL==0)
			{
				
				LCD_WR_REG(lcddev.setxcmd); 
				LCD_WR_DATA16(Xpos);
			
				LCD_WR_REG(lcddev.setycmd);
				LCD_WR_DATA16(Ypos);
				
		  }
			else
				{
					 LCD_WR_REG(lcddev.setxcmd); 
					 LCD_WR_DATA16(Xpos);
					
					 LCD_WR_REG(lcddev.setycmd);
					 LCD_WR_DATA16(Ypos);
			 }
	
}





//*******************************************************************/
//函数：void LCD_DrawPoint(u16 x,u16 y)
//函数功能：画点
//输入参数：
//x,y:坐标
//POINT_COLOR:此点的颜色
//*******************************************************************/

void LCD_DrawPoint(uint16_t x,uint16_t y)
{
	LCD_SetCursor(x,y);		//设置光标位置
	LCD_WriteRAM_Prepare();	//开始写入GRAM
	LCD_WR_DATA16(POINT_COLOR); 
}


//*******************************************************************/
//函数：void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
//函数功能：快速画点
//输入参数：
//x,y:坐标
//color:颜色
//*******************************************************************/

void LCD_Fast_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{	
     
    	LCD_SetCursor(x,y);		//设置光标位置
			LCD_WR_REG(lcddev.wramcmd); 
			LCD_WR_DATA16(color); //写入16位颜色

}	 





/**************************************************************************/
//函数：void LCD_Display_Dir(u8 dir)
//函数功能：设置LCD的显示方向及像素参数

//输入参数：

//设置LCD显示方向

////dir:   0,竖屏  正
//         1,竖屏  反
//         2,横屏  左
//         3,横屏  右
//*************************************************************************/
void LCD_Display_Dir(uint8_t dir)
{
	
		
	if(dir==0)			     //竖屏  正
	{
		lcddev.dir=0;	     //竖屏
		lcddev.width=LCD_X;
		lcddev.height=LCD_H;
    
		lcddev.wramcmd=0X2C;
	 	lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B;
		
    LCD_WriteReg(0x36,0xC0);//选择扫描方向
		
		USE_HORIZONTAL=0;   //方向设置： 		0,竖屏模式   1,横屏模式.
	

	}
	
else if (dir==1)			 //竖屏
	{	  				
		lcddev.dir=0;	     //竖屏
		lcddev.width=LCD_X;
		lcddev.height=LCD_H;
    
		lcddev.wramcmd=0X2C;
	 	lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B;
		
		LCD_WriteReg(0x36,0x40);//选择扫描方向
		
		USE_HORIZONTAL=0;   //方向设置： 		0,竖屏模式   1,横屏模式.
		

	} 	
	
	
	else if (dir==2)			//横屏
	{	  				
		lcddev.dir=1;	     //横屏
		lcddev.width=LCD_H;
		lcddev.height=LCD_X;

		lcddev.wramcmd=0X2C;
	 	lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B;  
		
		LCD_WriteReg(0x36,0xA0);//选择扫描方向
		
		USE_HORIZONTAL=1;   //方向设置： 		0,竖屏模式   1,横屏模式.
		

		
	} 
 else if (dir==3)				  //横屏
	{	  				
		lcddev.dir=1;	        //横屏
		lcddev.width=LCD_H;
		lcddev.height=LCD_X;

		lcddev.wramcmd=0X2C;
	 	lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B; 
    LCD_WriteReg(0x36,0x60);//选择扫描方向
		
		USE_HORIZONTAL=1;   //方向设置： 		0,竖屏模式   1,横屏模式.
		


	} 	
 else //设置默认为竖屏--正
 {
	  lcddev.dir=0;	     //竖屏
		lcddev.width=LCD_X;
		lcddev.height=LCD_H;
    
		lcddev.wramcmd=0X2C;
	 	lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B;

	  LCD_WriteReg(0x36,0xC0);//选择扫描方向
	 
	  USE_HORIZONTAL=0;   //方向设置： 		0,竖屏模式   1,横屏模式.
	 
	 
 }	 


//////以下设置，为窗口参数设置，设置了全屏的显示范围

   LCD_Set_Window(0,0,lcddev.width,lcddev.height);//设置全屏窗口
 
 
 

 	
}	


/**************************************************************************/
//函数：void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height)
//函数功能：设置LCD的显示窗口

//设置窗口,并自动设置画点坐标到窗口左上角(sx,sy).
//sx,sy:窗口起始坐标(左上角)
//width,height:窗口宽度和高度,必须大于0!!
//窗体大小:width*height.
//*************************************************************************/

void LCD_Set_Window(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{   
	
	
	  width=sx+width-1;
	  height=sy+height-1;
   if(USE_HORIZONTAL==0)
			 {
				 
				LCD_WR_REG(lcddev.setxcmd); 
				LCD_WR_DATA16(sx+2);      //设置 X方向起点
				LCD_WR_DATA16(width+2);   //设置 X方向终点
					
				LCD_WR_REG(lcddev.setycmd);
				LCD_WR_DATA16(sy+1);      //设置 Y方向起点
				LCD_WR_DATA16(height+1);  //设置 Y方向终点
				 
			 }
		 else
			 {
				  LCD_WR_REG(lcddev.setxcmd); 
					LCD_WR_DATA16(sx+1);      //设置 X方向起点
					LCD_WR_DATA16(width+1);   //设置 X方向终点
						
					LCD_WR_REG(lcddev.setycmd);
					LCD_WR_DATA16(sy+2);      //设置 Y方向起点
					LCD_WR_DATA16(height+2);  //设置 Y方向终点
				 
		  }
} 


/*******************************************************************************/
//函数：void LCD_Init(void)
//函数功能：初始化lcd
/*******************************************************************************/

void LCD_Init(void)
{ 	
	 
//   	  LCD_GPIO_Init();        //初始化驱动 I/O接口(在main.c中调用MX_GPIO_Init();之后再调用LCD_Init即可
	  SPI2_Init();
	  LCD_SoftRest();        //软复位
	
	  LCD_WR_REG(0x11);      //Sleep exit 
 	  HAL_Delay(120);      // delay 120 ms


 		//ST7735R Frame Rate
 		LCD_WR_REG(0xB1);
 		LCD_WR_DATA8(0x01);
 		LCD_WR_DATA8(0x2C);
 		LCD_WR_DATA8(0x2D);
 		LCD_WR_REG(0xB2);
 		LCD_WR_DATA8(0x01);
 		LCD_WR_DATA8(0x2C);
 		LCD_WR_DATA8(0x2D);
 		LCD_WR_REG(0xB3);
 		LCD_WR_DATA8(0x01);
 		LCD_WR_DATA8(0x2C);
 		LCD_WR_DATA8(0x2D);
 		LCD_WR_DATA8(0x01);
 		LCD_WR_DATA8(0x2C);
 		LCD_WR_DATA8(0x2D);
 		LCD_WR_REG(0xB4); //Column inversion
 		LCD_WR_DATA8(0x07);
 		//ST7735R Power Sequence
 		LCD_WR_REG(0xC0);
 		LCD_WR_DATA8(0xA2);
 		LCD_WR_DATA8(0x02);
 		LCD_WR_DATA8(0x84);
 		LCD_WR_REG(0xC1);
 		LCD_WR_DATA8(0xC5);
 		LCD_WR_REG(0xC2);
 		LCD_WR_DATA8(0x0A);
 		LCD_WR_DATA8(0x00);
 		LCD_WR_REG(0xC3);
 		LCD_WR_DATA8(0x8A);
 		LCD_WR_DATA8(0x2A);
 		LCD_WR_REG(0xC4);
 		LCD_WR_DATA8(0x8A);
 		LCD_WR_DATA8(0xEE);
 		LCD_WR_REG(0xC5); //VCOM
 		LCD_WR_DATA8(0x0E);
 		LCD_WR_REG(0x36); //MX, MY, RGB mode
 		LCD_WR_DATA8(0xC0);
 		//ST7735R Gamma Sequence
 		LCD_WR_REG(0xe0);
 		LCD_WR_DATA8(0x0f);
 		LCD_WR_DATA8(0x1a);
 		LCD_WR_DATA8(0x0f);
 		LCD_WR_DATA8(0x18);
 		LCD_WR_DATA8(0x2f);
 		LCD_WR_DATA8(0x28);
 		LCD_WR_DATA8(0x20);
 		LCD_WR_DATA8(0x22);
 		LCD_WR_DATA8(0x1f);
 		LCD_WR_DATA8(0x1b);
 		LCD_WR_DATA8(0x23);
 		LCD_WR_DATA8(0x37);
 		LCD_WR_DATA8(0x00);
 		LCD_WR_DATA8(0x07);
 		LCD_WR_DATA8(0x02);
 		LCD_WR_DATA8(0x10);
 		LCD_WR_REG(0xe1);
 		LCD_WR_DATA8(0x0f);
 		LCD_WR_DATA8(0x1b);
 		LCD_WR_DATA8(0x0f);
 		LCD_WR_DATA8(0x17);
 		LCD_WR_DATA8(0x33);
 		LCD_WR_DATA8(0x2c);
 		LCD_WR_DATA8(0x29);
 		LCD_WR_DATA8(0x2e);
 		LCD_WR_DATA8(0x30);
 		LCD_WR_DATA8(0x30);
 		LCD_WR_DATA8(0x39);
 		LCD_WR_DATA8(0x3f);
 		LCD_WR_DATA8(0x00);
 		LCD_WR_DATA8(0x07);
 		LCD_WR_DATA8(0x03);
 		LCD_WR_DATA8(0x10);
 		LCD_WR_REG(0x2a);
 		LCD_WR_DATA8(0x00);
 		LCD_WR_DATA8(0x00);
 		LCD_WR_DATA8(0x00);
 		LCD_WR_DATA8(0x7f);
 		LCD_WR_REG(0x2b);
 		LCD_WR_DATA8(0x00);
 		LCD_WR_DATA8(0x00);
 		LCD_WR_DATA8(0x00);
 		LCD_WR_DATA8(0x9f);
 		LCD_WR_REG(0xF0); //Enable test command
 		LCD_WR_DATA8(0x01);
 		LCD_WR_REG(0xF6); //Disable ram power save mode
 		LCD_WR_DATA8(0x00);
 		LCD_WR_REG(0x3A); //65k mode
 		LCD_WR_DATA8(0x05);
 		LCD_WR_REG(0x29);//Display on

	  LCD_Display_Dir(LCD_DIR_Mode);	//选择--屏幕显示方式

//      LCD_BLK_SET;               //点亮背光

	  LCD_Clear(WHITE);
	
	
	
}


////////////////////////////////////以下函数是屏幕显示图形的简单驱动函数//////////////////////////////////////////////////



/*******************************************************************************/
//函数：void LCD_Clear(u16 color)
//函数功能：全屏清屏填充函数
//输入参数：
//color:要清屏的填充色
/*******************************************************************************/

void LCD_Clear(uint16_t color)
{
	uint32_t index=0;
	uint32_t totalpoint;
	
	LCD_Set_Window(0,0,lcddev.width,lcddev.height);//设置全屏窗口
	
	totalpoint=lcddev.width * lcddev.height; 			//得到总点数
 
	LCD_SetCursor(0,0);	//设置光标位置
	
	LCD_WriteRAM_Prepare();     		//开始写入GRAM
	
	for(index=0;index<totalpoint;index++)
	{
		LCD_WR_DATA16(color);	
	}
} 


/*******************************************************************************/
//函数：void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)

//函数功能：区域填充函数--填充单个颜色
//输入参数：
//在指定区域内填充单个颜色
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)
//color:要填充的颜色
/*******************************************************************************/

void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{          
		uint32_t i;
		uint32_t xlen=0;

    //设置窗口
	
	  LCD_Set_Window(sx,sy,ex-sx,ey-sy);//设置窗口
 	
	  LCD_WR_REG(lcddev.wramcmd);	  
	
 		xlen=(ex-sx)*(ey-sy);//计算出总共需要写入的点数
		
		LCD_WriteRAM_Prepare();     			//开始写入GRAM
		
		for(i=0;i<=xlen;i++)
		{
		 	LCD_WR_DATA16(color);	//显示颜色
		}


		//恢复全屏窗口
				
		//以下设置，为窗口参数设置，设置了全屏的显示范围
			
    LCD_Set_Window(0,0,lcddev.width,lcddev.height);//设置全屏窗口
		 
}


/*******************************************************************************/
//函数：void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)

//函数功能：区域填充函数
//输入参数：
//在指定区域内填充指定颜色块
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)
//color:要填充的颜色
/*******************************************************************************/

void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
{  

		uint32_t i;
		uint32_t xlen=0;

 //设置窗口

    LCD_Set_Window(sx,sy,ex-sx,ey-sy);//设置窗口
		  	
	  LCD_WR_REG(lcddev.wramcmd);	  
	
 		xlen=(ex-sx)*(ey-sy);//计算出总共需要写入的点数
		
		LCD_WriteRAM_Prepare();     			//开始写入GRAM
		
		for(i=0;i<=xlen;i++)
		{
		 	LCD_WR_DATA16(*color);	//显示颜色
		}


	//以下设置，为窗口参数设置，设置了全屏的显示范围
			
    LCD_Set_Window(0,0,lcddev.width,lcddev.height);//设置全屏窗口
		

}



/*******************************************************************************/
//函数：void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
//函数功能：画线
//输入参数：
//x1,y1:起点坐标
//x2,y2:终点坐标
//Color;线条颜色
/*******************************************************************************/

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t Color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	
	delta_x=x2-x1; //计算坐标增量
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	
	
	if(delta_x>0)incx=1; //设置单步方向
	else if(delta_x==0)incx=0;//垂直线
	else
     {
		    incx=-1;
		    delta_x=-delta_x;
		 }

	
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线
	else
     { 
		   incy=-1;
		   delta_y=-delta_y;
		 }

	
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴
	else distance=delta_y; 
	
	for(t=0;t<=distance+1;t++ )//画线输出
	{  
		LCD_Fast_DrawPoint(uRow,uCol,Color);//画点 --使用输入颜色参数
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

/*******************************************************************************/
//函数：void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
//函数功能：画矩形
//输入参数：
//(x1,y1),(x2,y2):矩形的对角坐标
//Color;线条颜色
/*******************************************************************************/

void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t Color)
{
	LCD_DrawLine(x1,y1,x2,y1,Color);
	LCD_DrawLine(x1,y1,x1,y2,Color);
	LCD_DrawLine(x1,y2,x2,y2,Color);
	LCD_DrawLine(x2,y1,x2,y2,Color);
}

/*******************************************************************************/
//函数：void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
//函数功能：在指定位置画一个指定大小的圆
//输入参数：
//(x,y):中心点
//r    :半径
//Color;线条颜色
/*******************************************************************************/

void LCD_Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r, uint16_t Color)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		LCD_Fast_DrawPoint(x0+a,y0-b,Color);             //5
 		LCD_Fast_DrawPoint(x0+b,y0-a,Color);             //0           
		LCD_Fast_DrawPoint(x0+b,y0+a,Color);             //4               
		LCD_Fast_DrawPoint(x0+a,y0+b,Color);             //6 
		LCD_Fast_DrawPoint(x0-a,y0+b,Color);             //1       
 		LCD_Fast_DrawPoint(x0-b,y0+a,Color);             
		LCD_Fast_DrawPoint(x0-a,y0-b,Color);             //2             
  	LCD_Fast_DrawPoint(x0-b,y0-a,Color);             //7     	         
		a++;
		//使用Bresenham算法画圆
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
}


/*******************************************************************************/
//函数：LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u16 color,u8 mode)
//函数功能：在指定位置显示一个字符
//输入参数：
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16/24
//color,字符颜色
//mode:叠加方式(1)还是非叠加方式(0)
/*******************************************************************************/

void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint16_t color,uint8_t mode)
{  							  
    uint8_t temp,t1,t;
	uint16_t y0=y;
	uint8_t csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数
	//设置窗口
	num=num-' ';//得到偏移后的值
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num][t]; 	 	//调用1206字体
		else if(size==16)temp=asc2_1608[num][t];	//调用1608字体
		else if(size==24)temp=asc2_2412[num][t];	//调用2412字体
		else return;								//没有的字库
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_Fast_DrawPoint(x,y,color);
			else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR);
			
			temp<<=1;
			y++;
			if(y>=lcddev.height)return;		//超区域了
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=lcddev.width)return;	//超区域了
				break;
			}
		}  	 
	}  	    	   	 	  
}



/*******************************************************************************/
//函数：u32 LCD_Pow(u8 m,u8 n)
//函数功能：m^n函数
//输入参数：两个8位数据
//返回值:m^n次方.
/*******************************************************************************/
uint32_t LCD_Pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}	


/*******************************************************************************/
//函数：void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size,u16 color)
//函数功能：显示数字,高位为0,则不显示
//输入参数：

//x,y :起点坐标
//num:数值(0~4294967295);
//len :数字的位数
//size:字体大小
//color:颜色
//返回值:无
/*******************************************************************************/

void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint16_t color)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,color,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,color,0); 
	}
} 



/*******************************************************************************/
//函数：void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u16 color,u8 mode)
//函数功能：显示数字,高位为0,还是显示
//输入参数：
//显示数字,高位为0,还是显示
//x,y:起点坐标
//num:数值(0~999999999);
//len:长度(即要显示的位数)
//size:字体大小
//color:颜色
//mode:
//[7]:0,不填充;1,填充0.
//[6:1]:保留
//[0]:0,非叠加显示;1,叠加显示.
/*******************************************************************************/

void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint16_t color,uint8_t mode)
{  
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,color,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,color,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,color,mode&0X01); 
	}
} 

/*******************************************************************************/
//函数：void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u16 color,u8 *p)
//函数功能：显示字符串
//输入参数：
//x,y:起点坐标
//width,height:区域大小
//size:字体大小
//color:颜色
//*p:字符串起始地址
/*******************************************************************************/


void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint16_t color,uint8_t *p)
{         
	uint8_t x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//退出
        LCD_ShowChar(x,y,*p,size,color,0);
        x+=size/2;
        p++;
    }  
}

//****************************************************************************************/
//函数：void DisplayButtonDown(u16 x1,u16 y1,u16 x2,u16 y2)
//功能描述: 在屏幕显示一凸起的按钮框
//输    入: u16 x1,y1,x2,y2 按钮框左上角和右下角坐标
//输    出: 无
/****************************************************************************************/

void DisplayButtonDown(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	
	LCD_DrawLine(x1,y1, x2,y1,GRAY2);  //H
		
	LCD_DrawLine(x1+1,y1+1,x2,y1+1,GRAY1);  //H
		
	LCD_DrawLine(x1,  y1,  x1,y2,GRAY2);    //V
		
	LCD_DrawLine(x1+1,y1+1,x1+1,y2,GRAY1);  //V
	
	LCD_DrawLine(x1, y2, x2, y2,WHITE);     //H
	LCD_DrawLine(x2, y1, x2, y2,WHITE);     //V
}

//****************************************************************************************/
//函数：void DisplayButtonUp(u16 x1,u16 y1,u16 x2,u16 y2)
//功能描述: 在屏幕显示一凹下的按钮框
//输    入: u16 x1,y1,x2,y2 按钮框左上角和右下角坐标
//输    出: 无
/****************************************************************************************/
void DisplayButtonUp(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	
	LCD_DrawLine(x1,  y1,  x2,y1,WHITE);    //H
	LCD_DrawLine(x1,  y1,  x1,y2,WHITE);    //V
	
	LCD_DrawLine(x1+1,y2-1,x2,y2-1,GRAY1);  //H
		
	LCD_DrawLine(x1,  y2,  x2,y2,GRAY2);    //H
		
	LCD_DrawLine(x2-1,y1+1,x2-1,y2,GRAY1);  //V
		
    LCD_DrawLine(x2  ,y1  ,x2,y2,GRAY2);    //V
	

}


//****************************************************************************************/
//函数：void Draw_Test(void)
//功能描述: 绘制图形函数测试
/****************************************************************************************/

void Draw_Test(void)
{
      LCD_Clear(WHITE); //清屏
		
	  LCD_DrawLine(20,20, lcddev.width-20,lcddev.height-20,RED);//划线函数
	  LCD_DrawLine(20,lcddev.height-20, lcddev.width-20, 20,RED);//划线函数
	
	  LCD_DrawRectangle(20,20,lcddev.width-20,lcddev.height-20, BLUE);//绘制方形状
	  
	  LCD_Draw_Circle(lcddev.width/2,lcddev.height/2,lcddev.width/3-1, BRED);//绘制圆形
	  LCD_Draw_Circle(lcddev.width/2,lcddev.height/2,lcddev.width/3, BRED);//绘制圆形
	  LCD_Draw_Circle(lcddev.width/2,lcddev.height/2,lcddev.width/3+1, BRED);//绘制圆形
			
	  HAL_Delay(2000);//延时

}


//****************************************************************************************/
//函数：void Color_Test(void)
//功能描述: 颜色填充显示测试
/****************************************************************************************/

void Color_Test(void)
{
	
		LCD_Clear(WHITE); //清屏
		
		Draw_Font16B(8,16,BLUE,"1:颜色填充测试");
	
	    HAL_Delay(1000);
	
	    LCD_Fill(5,5,lcddev.width-5,lcddev.height-5,RED);//设置一个窗口，写入指定区域颜色
	
	    LCD_Fill(20,20,lcddev.width-20,lcddev.height-20,YELLOW);//设置一个窗口，写入指定区域颜色

	    LCD_Fill(50,50,lcddev.width-50,lcddev.height-50,BLUE);//设置一个窗口，写入指定区域颜色
	
	    LCD_Fill(60,70,lcddev.width-60,lcddev.height-70,MAGENTA);//设置一个窗口，写入指定区域颜色
	
		HAL_Delay(1000);

		LCD_Clear(WHITE);
	
	    Draw_Test();//绘图函数测试
	
		HAL_Delay(300);//延时
		LCD_Clear(BLACK);
		HAL_Delay(300);//延时
		LCD_Clear(RED);
		HAL_Delay(300);//延时
		LCD_Clear(YELLOW);
		HAL_Delay(300);//延时
		LCD_Clear(GREEN);
		HAL_Delay(300);//延时
		LCD_Clear(BLUE);
		HAL_Delay(300);//延时

}


uint16_t D_Color=BLUE; //点阵颜色
uint16_t B_Color=WHITE; //背景颜色

//****************************************************************************************/
//函数：void Font_Test(void)
//功能描述: 字体字形显示测试
/****************************************************************************************/

void Font_Test(void)
{
	LCD_Clear(WHITE);
	Draw_Font16B(8,16,BLUE,"2:文字显示测试");

	HAL_Delay(1000);
	LCD_Clear(WHITE);

	Draw_Font16B(4,20,RED,"0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz");

	HAL_Delay(1000);	
	
	LCD_Clear(WHITE);


}


//****************************************************************************************/
//函数：void Demo_Menu(void)
//功能描述: 演示程序菜单
/****************************************************************************************/

void Demo_Menu(void)
{

	LCD_Clear(WHITE); //清屏
	

	Draw_Font24B(4,30,RED,"液晶屏测试");

	Draw_Font16B(4,60,BLUE,"1: 颜色填充");

	Draw_Font16B(4,80,BLUE,"2: 文字显示");

	Draw_Font16B(4,100,BLUE,"3: 图片显示");

	Draw_Font16B(4,120,RED,"hello world");
	Draw_Font16B(4,140,RED,"yyds");

	HAL_Delay(2000);//延时
		
	Color_Test();       //颜色填充测试
    Font_Test();        //字体字形显示测试
//    GBK_LibFont_Test(); //GBK字库测试 -(如果使用不带字库的液晶屏版本，此处可以屏蔽，不做字库测试）
// 	Show_Picture();     //显示一张图片
}
