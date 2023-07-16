#include "lcd.h"


//////////////////////////////////////////////////////////////////////////////////	 

//1.8��  LCD Һ������	  оƬ��ST7735s

//********************************************************************************

//////////////////////////////////////////////////////////////////////////////////	 
				 
//LCD�Ļ�����ɫ�ͱ���ɫ

uint16_t POINT_COLOR=0x0000;	//������ɫ
uint16_t BACK_COLOR=0xFFFF;  //����ɫ

uint8_t USE_HORIZONTAL=0;    //�������ã� 		0,����ģʽ   1,����ģʽ.


//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;


//����������ʹ�õ���MCUӲ��SPI�ӿ�����


/******************************************************************************

  �ӿڶ��壬����ݽ����޸Ĳ��޸���ӦIO��ʼ��--�������Ӻ�IOҪ��Ӧ

	#define LCD_SDA        	//PB15      //����������
	#define LCD_SCL        	//PB13      //ʱ����
	#define LCD_CS        	//PB12      //Ƭѡ
	#define LCD_SDO/RST     //PB14      //�������/��λ	RES
	#define LCD_RS         	//PC5       //����/�����л�DC
	#define LCD_BLK         //PB1    	  //�������


*******************************************************************************/


/******************************************************************************/

//������ void SPI2_Init(void)

//�������ܣ������� Ӳ��SPIģ��ĳ�ʼ�����룬���ó�����ģʽ
//SPI�ڳ�ʼ��
//�������Ƕ�SPI2�ĳ�ʼ��
/******************************************************************************/


void SPI2_Init(void)
{

    MX_SPI2_Init();
	SPI2_ReadWriteByte(0xff);//��������
	
}



/******************************************************************************/

//������ void LCD_GPIO_Init(void)

//�������ܣ�����Һ��IO��ʼ������

//	#define LCD_SDA        	//PB15      //����������
//	#define LCD_SCL        	//PB13      //ʱ����
//	#define LCD_CS        	//PB12      //Ƭѡ
//	#define LCD_SDO/RST     //PB14      //�������/��λRES
//	#define LCD_RS         	//PB1       //����/�����л�DC
//	#define LCD_BLK         //PA8    	  //�������BL

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



//    SPI2_Init();           //��ʼ��Ӳ��SPI2

////  LCD_HardwareRest();   //Ӳ��λ--���IO���ӣ�Ӳ����λ�ɿ���Ч

//}


/********************************************************************/
//������u8 SPI2_ReadWriteByte(u8 TxData)
//�������ܣ� SPI��д���� �� ʹ�ò����Ĵ�����ʽ���ٶȸ���

//SPI1 ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
//*******************************************************************/

uint8_t SPI2_ReadWriteByte(uint8_t TxData)
{

    HAL_SPI_Transmit(&hspi2,&TxData, sizeof(TxData) ,HAL_MAX_DELAY);                                //����ͨ��SPIx������յ�����

}




//********************************************************************/

//������void LCD_WR_REG(u16 regval)
//�������ܣ�
//д�Ĵ�������
//regval:�Ĵ���ֵ
//*******************************************************************/

void LCD_WR_REG(uint16_t regval)
{
     LCD_CS_CLR;//LCD_CS=0  //Ƭѡ
     LCD_RS_CLR;  //LCD_RS=0  //��������״̬
	 SPI2_ReadWriteByte(regval&0x00FF);
     LCD_CS_SET;  //LCD_CS=1
}



//*******************************************************************/

//������void LCD_WR_DATA8(u8 data)   //д8λ����
//�������ܣ�
//Һ����--д8λ���ݺ���
//*******************************************************************/


void LCD_WR_DATA8(uint8_t data)   //д8λ����
{
    LCD_CS_CLR;  //LCD_CS=0  //Ƭѡ
    LCD_RS_SET;	 //LCD_RS=1   //��������״̬
	SPI2_ReadWriteByte(data);
    LCD_CS_SET;  //LCD_CS=1
}


//*******************************************************************/
//������void LCD_WR_DATA16(u16 data)   //д16λ����
//�������ܣ�дLCD����
//���������
//data:Ҫд���ֵ
//*******************************************************************/


void LCD_WR_DATA16(uint16_t data)
{

    LCD_CS_CLR;  //LCD_CS=0  //Ƭѡ
    LCD_RS_SET;	 //LCD_RS=1   //��������״̬
	SPI2_ReadWriteByte(data>>8);
	SPI2_ReadWriteByte(data);
    LCD_CS_SET;    //LCD_CS=1
	
}


//*******************************************************************/

//������void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue)  //дҺ�����Ĵ���

//�������ܣ�д�Ĵ���

//�������:
//LCD_Reg:�Ĵ�����ַ
//LCD_RegValue:Ҫд�������
//*******************************************************************/

void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg);		   //д��Ҫд�ļĴ������
	LCD_WR_DATA8(LCD_RegValue);//д������
}


//*******************************************************************/
//������void LCD_WriteRAM_Prepare(void)
//�������ܣ���ʼдGRAM  ����
//*******************************************************************/

void LCD_WriteRAM_Prepare(void)
{
 	LCD_WR_REG(lcddev.wramcmd);	  
}	



//*******************************************************************/
//������LCD_WriteRAM(u16 RGB_Code)
//�������ܣ�д�������ɫֵ
//�������:
//RGB_Code:��ɫֵ
//*******************************************************************/

void LCD_WriteRAM(uint16_t RGB_Code)
{							    
	LCD_WR_DATA16( RGB_Code );//дʮ��λGRAM
}





//********************************************************************************/
//������void LCD_DisplayOn(void)
//�������ܣ�
//LCD������ʾ
//*******************************************************************/
void LCD_DisplayOn(void)
{					   
	LCD_WR_REG(0X29);	//������ʾ
}	


//*******************************************************************/
//������void LCD_DisplayOff(void)
//�������ܣ�
//LCD�ر���ʾ
//*******************************************************************/

void LCD_DisplayOff(void)
{	   
	LCD_WR_REG(0X28);	//�ر���ʾ

} 

//********************************************************************************/
//������void LCD_SoftRest(void)
//�������ܣ�����Ļ�����ִ����λ����
//LCD������ʾ
//*******************************************************************/
void LCD_SoftRest(void)
{					   
//	LCD_WR_REG(0x01);	//������λ����
	LCD_RST_CLR;
	HAL_Delay(100);
	LCD_RST_SET;
	HAL_Delay(50);      // delay 50 ms
}	


//********************************************************************************/
//������void LCD_SoftRest(void)
//�������ܣ�����Ļ�����ִ����λ����
//LCD������ʾ
//*******************************************************************/
void LCD_HardwareRest(void)
{
    LCD_RS_CLR;     //Һ������λ --Ӳ��λ--ʹ��       //PB14��ΪҺ������λ��������
	HAL_Delay(50);      // delay 50 ms
    LCD_RS_SET; //Һ������λ --Ӳ��λ--ʧ��       //PB14��ΪҺ������λ��������
	HAL_Delay(30);      // delay 30 ms
}	



//*******************************************************************/
//������void LCD_SetCursor(u16 Xpos, u16 Ypos)
//�������ܣ����ù��λ��
//���������
//Xpos:������
//Ypos:������
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
//������void LCD_DrawPoint(u16 x,u16 y)
//�������ܣ�����
//���������
//x,y:����
//POINT_COLOR:�˵����ɫ
//*******************************************************************/

void LCD_DrawPoint(uint16_t x,uint16_t y)
{
	LCD_SetCursor(x,y);		//���ù��λ��
	LCD_WriteRAM_Prepare();	//��ʼд��GRAM
	LCD_WR_DATA16(POINT_COLOR); 
}


//*******************************************************************/
//������void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
//�������ܣ����ٻ���
//���������
//x,y:����
//color:��ɫ
//*******************************************************************/

void LCD_Fast_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{	
     
    	LCD_SetCursor(x,y);		//���ù��λ��
			LCD_WR_REG(lcddev.wramcmd); 
			LCD_WR_DATA16(color); //д��16λ��ɫ

}	 





/**************************************************************************/
//������void LCD_Display_Dir(u8 dir)
//�������ܣ�����LCD����ʾ�������ز���

//���������

//����LCD��ʾ����

////dir:   0,����  ��
//         1,����  ��
//         2,����  ��
//         3,����  ��
//*************************************************************************/
void LCD_Display_Dir(uint8_t dir)
{
	
		
	if(dir==0)			     //����  ��
	{
		lcddev.dir=0;	     //����
		lcddev.width=LCD_X;
		lcddev.height=LCD_H;
    
		lcddev.wramcmd=0X2C;
	 	lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B;
		
    LCD_WriteReg(0x36,0xC0);//ѡ��ɨ�跽��
		
		USE_HORIZONTAL=0;   //�������ã� 		0,����ģʽ   1,����ģʽ.
	

	}
	
else if (dir==1)			 //����
	{	  				
		lcddev.dir=0;	     //����
		lcddev.width=LCD_X;
		lcddev.height=LCD_H;
    
		lcddev.wramcmd=0X2C;
	 	lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B;
		
		LCD_WriteReg(0x36,0x40);//ѡ��ɨ�跽��
		
		USE_HORIZONTAL=0;   //�������ã� 		0,����ģʽ   1,����ģʽ.
		

	} 	
	
	
	else if (dir==2)			//����
	{	  				
		lcddev.dir=1;	     //����
		lcddev.width=LCD_H;
		lcddev.height=LCD_X;

		lcddev.wramcmd=0X2C;
	 	lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B;  
		
		LCD_WriteReg(0x36,0xA0);//ѡ��ɨ�跽��
		
		USE_HORIZONTAL=1;   //�������ã� 		0,����ģʽ   1,����ģʽ.
		

		
	} 
 else if (dir==3)				  //����
	{	  				
		lcddev.dir=1;	        //����
		lcddev.width=LCD_H;
		lcddev.height=LCD_X;

		lcddev.wramcmd=0X2C;
	 	lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B; 
    LCD_WriteReg(0x36,0x60);//ѡ��ɨ�跽��
		
		USE_HORIZONTAL=1;   //�������ã� 		0,����ģʽ   1,����ģʽ.
		


	} 	
 else //����Ĭ��Ϊ����--��
 {
	  lcddev.dir=0;	     //����
		lcddev.width=LCD_X;
		lcddev.height=LCD_H;
    
		lcddev.wramcmd=0X2C;
	 	lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B;

	  LCD_WriteReg(0x36,0xC0);//ѡ��ɨ�跽��
	 
	  USE_HORIZONTAL=0;   //�������ã� 		0,����ģʽ   1,����ģʽ.
	 
	 
 }	 


//////�������ã�Ϊ���ڲ������ã�������ȫ������ʾ��Χ

   LCD_Set_Window(0,0,lcddev.width,lcddev.height);//����ȫ������
 
 
 

 	
}	


/**************************************************************************/
//������void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height)
//�������ܣ�����LCD����ʾ����

//���ô���,���Զ����û������굽�������Ͻ�(sx,sy).
//sx,sy:������ʼ����(���Ͻ�)
//width,height:���ڿ�Ⱥ͸߶�,�������0!!
//�����С:width*height.
//*************************************************************************/

void LCD_Set_Window(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{   
	
	
	  width=sx+width-1;
	  height=sy+height-1;
   if(USE_HORIZONTAL==0)
			 {
				 
				LCD_WR_REG(lcddev.setxcmd); 
				LCD_WR_DATA16(sx+2);      //���� X�������
				LCD_WR_DATA16(width+2);   //���� X�����յ�
					
				LCD_WR_REG(lcddev.setycmd);
				LCD_WR_DATA16(sy+1);      //���� Y�������
				LCD_WR_DATA16(height+1);  //���� Y�����յ�
				 
			 }
		 else
			 {
				  LCD_WR_REG(lcddev.setxcmd); 
					LCD_WR_DATA16(sx+1);      //���� X�������
					LCD_WR_DATA16(width+1);   //���� X�����յ�
						
					LCD_WR_REG(lcddev.setycmd);
					LCD_WR_DATA16(sy+2);      //���� Y�������
					LCD_WR_DATA16(height+2);  //���� Y�����յ�
				 
		  }
} 


/*******************************************************************************/
//������void LCD_Init(void)
//�������ܣ���ʼ��lcd
/*******************************************************************************/

void LCD_Init(void)
{ 	
	 
//   	  LCD_GPIO_Init();        //��ʼ������ I/O�ӿ�(��main.c�е���MX_GPIO_Init();֮���ٵ���LCD_Init����
	  SPI2_Init();
	  LCD_SoftRest();        //��λ
	
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

	  LCD_Display_Dir(LCD_DIR_Mode);	//ѡ��--��Ļ��ʾ��ʽ

//      LCD_BLK_SET;               //��������

	  LCD_Clear(WHITE);
	
	
	
}


////////////////////////////////////���º�������Ļ��ʾͼ�εļ���������//////////////////////////////////////////////////



/*******************************************************************************/
//������void LCD_Clear(u16 color)
//�������ܣ�ȫ��������亯��
//���������
//color:Ҫ���������ɫ
/*******************************************************************************/

void LCD_Clear(uint16_t color)
{
	uint32_t index=0;
	uint32_t totalpoint;
	
	LCD_Set_Window(0,0,lcddev.width,lcddev.height);//����ȫ������
	
	totalpoint=lcddev.width * lcddev.height; 			//�õ��ܵ���
 
	LCD_SetCursor(0,0);	//���ù��λ��
	
	LCD_WriteRAM_Prepare();     		//��ʼд��GRAM
	
	for(index=0;index<totalpoint;index++)
	{
		LCD_WR_DATA16(color);	
	}
} 


/*******************************************************************************/
//������void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)

//�������ܣ�������亯��--��䵥����ɫ
//���������
//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)
//color:Ҫ������ɫ
/*******************************************************************************/

void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{          
		uint32_t i;
		uint32_t xlen=0;

    //���ô���
	
	  LCD_Set_Window(sx,sy,ex-sx,ey-sy);//���ô���
 	
	  LCD_WR_REG(lcddev.wramcmd);	  
	
 		xlen=(ex-sx)*(ey-sy);//������ܹ���Ҫд��ĵ���
		
		LCD_WriteRAM_Prepare();     			//��ʼд��GRAM
		
		for(i=0;i<=xlen;i++)
		{
		 	LCD_WR_DATA16(color);	//��ʾ��ɫ
		}


		//�ָ�ȫ������
				
		//�������ã�Ϊ���ڲ������ã�������ȫ������ʾ��Χ
			
    LCD_Set_Window(0,0,lcddev.width,lcddev.height);//����ȫ������
		 
}


/*******************************************************************************/
//������void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)

//�������ܣ�������亯��
//���������
//��ָ�����������ָ����ɫ��
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)
//color:Ҫ������ɫ
/*******************************************************************************/

void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
{  

		uint32_t i;
		uint32_t xlen=0;

 //���ô���

    LCD_Set_Window(sx,sy,ex-sx,ey-sy);//���ô���
		  	
	  LCD_WR_REG(lcddev.wramcmd);	  
	
 		xlen=(ex-sx)*(ey-sy);//������ܹ���Ҫд��ĵ���
		
		LCD_WriteRAM_Prepare();     			//��ʼд��GRAM
		
		for(i=0;i<=xlen;i++)
		{
		 	LCD_WR_DATA16(*color);	//��ʾ��ɫ
		}


	//�������ã�Ϊ���ڲ������ã�������ȫ������ʾ��Χ
			
    LCD_Set_Window(0,0,lcddev.width,lcddev.height);//����ȫ������
		

}



/*******************************************************************************/
//������void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
//�������ܣ�����
//���������
//x1,y1:�������
//x2,y2:�յ�����
//Color;������ɫ
/*******************************************************************************/

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t Color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	
	delta_x=x2-x1; //������������
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	
	
	if(delta_x>0)incx=1; //���õ�������
	else if(delta_x==0)incx=0;//��ֱ��
	else
     {
		    incx=-1;
		    delta_x=-delta_x;
		 }

	
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ��
	else
     { 
		   incy=-1;
		   delta_y=-delta_y;
		 }

	
	if( delta_x>delta_y)distance=delta_x; //ѡȡ��������������
	else distance=delta_y; 
	
	for(t=0;t<=distance+1;t++ )//�������
	{  
		LCD_Fast_DrawPoint(uRow,uCol,Color);//���� --ʹ��������ɫ����
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
//������void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
//�������ܣ�������
//���������
//(x1,y1),(x2,y2):���εĶԽ�����
//Color;������ɫ
/*******************************************************************************/

void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t Color)
{
	LCD_DrawLine(x1,y1,x2,y1,Color);
	LCD_DrawLine(x1,y1,x1,y2,Color);
	LCD_DrawLine(x1,y2,x2,y2,Color);
	LCD_DrawLine(x2,y1,x2,y2,Color);
}

/*******************************************************************************/
//������void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
//�������ܣ���ָ��λ�û�һ��ָ����С��Բ
//���������
//(x,y):���ĵ�
//r    :�뾶
//Color;������ɫ
/*******************************************************************************/

void LCD_Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r, uint16_t Color)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
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
		//ʹ��Bresenham�㷨��Բ
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
}


/*******************************************************************************/
//������LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u16 color,u8 mode)
//�������ܣ���ָ��λ����ʾһ���ַ�
//���������
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16/24
//color,�ַ���ɫ
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
/*******************************************************************************/

void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint16_t color,uint8_t mode)
{  							  
    uint8_t temp,t1,t;
	uint16_t y0=y;
	uint8_t csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���
	//���ô���
	num=num-' ';//�õ�ƫ�ƺ��ֵ
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num][t]; 	 	//����1206����
		else if(size==16)temp=asc2_1608[num][t];	//����1608����
		else if(size==24)temp=asc2_2412[num][t];	//����2412����
		else return;								//û�е��ֿ�
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_Fast_DrawPoint(x,y,color);
			else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR);
			
			temp<<=1;
			y++;
			if(y>=lcddev.height)return;		//��������
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=lcddev.width)return;	//��������
				break;
			}
		}  	 
	}  	    	   	 	  
}



/*******************************************************************************/
//������u32 LCD_Pow(u8 m,u8 n)
//�������ܣ�m^n����
//�������������8λ����
//����ֵ:m^n�η�.
/*******************************************************************************/
uint32_t LCD_Pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}	


/*******************************************************************************/
//������void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size,u16 color)
//�������ܣ���ʾ����,��λΪ0,����ʾ
//���������

//x,y :�������
//num:��ֵ(0~4294967295);
//len :���ֵ�λ��
//size:�����С
//color:��ɫ
//����ֵ:��
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
//������void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u16 color,u8 mode)
//�������ܣ���ʾ����,��λΪ0,������ʾ
//���������
//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//color:��ɫ
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
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
//������void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u16 color,u8 *p)
//�������ܣ���ʾ�ַ���
//���������
//x,y:�������
//width,height:�����С
//size:�����С
//color:��ɫ
//*p:�ַ�����ʼ��ַ
/*******************************************************************************/


void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint16_t color,uint8_t *p)
{         
	uint8_t x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*p,size,color,0);
        x+=size/2;
        p++;
    }  
}

//****************************************************************************************/
//������void DisplayButtonDown(u16 x1,u16 y1,u16 x2,u16 y2)
//��������: ����Ļ��ʾһ͹��İ�ť��
//��    ��: u16 x1,y1,x2,y2 ��ť�����ϽǺ����½�����
//��    ��: ��
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
//������void DisplayButtonUp(u16 x1,u16 y1,u16 x2,u16 y2)
//��������: ����Ļ��ʾһ���µİ�ť��
//��    ��: u16 x1,y1,x2,y2 ��ť�����ϽǺ����½�����
//��    ��: ��
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
//������void Draw_Test(void)
//��������: ����ͼ�κ�������
/****************************************************************************************/

void Draw_Test(void)
{
      LCD_Clear(WHITE); //����
		
	  LCD_DrawLine(20,20, lcddev.width-20,lcddev.height-20,RED);//���ߺ���
	  LCD_DrawLine(20,lcddev.height-20, lcddev.width-20, 20,RED);//���ߺ���
	
	  LCD_DrawRectangle(20,20,lcddev.width-20,lcddev.height-20, BLUE);//���Ʒ���״
	  
	  LCD_Draw_Circle(lcddev.width/2,lcddev.height/2,lcddev.width/3-1, BRED);//����Բ��
	  LCD_Draw_Circle(lcddev.width/2,lcddev.height/2,lcddev.width/3, BRED);//����Բ��
	  LCD_Draw_Circle(lcddev.width/2,lcddev.height/2,lcddev.width/3+1, BRED);//����Բ��
			
	  HAL_Delay(2000);//��ʱ

}


//****************************************************************************************/
//������void Color_Test(void)
//��������: ��ɫ�����ʾ����
/****************************************************************************************/

void Color_Test(void)
{
	
		LCD_Clear(WHITE); //����
		
		Draw_Font16B(8,16,BLUE,"1:��ɫ������");
	
	    HAL_Delay(1000);
	
	    LCD_Fill(5,5,lcddev.width-5,lcddev.height-5,RED);//����һ�����ڣ�д��ָ��������ɫ
	
	    LCD_Fill(20,20,lcddev.width-20,lcddev.height-20,YELLOW);//����һ�����ڣ�д��ָ��������ɫ

	    LCD_Fill(50,50,lcddev.width-50,lcddev.height-50,BLUE);//����һ�����ڣ�д��ָ��������ɫ
	
	    LCD_Fill(60,70,lcddev.width-60,lcddev.height-70,MAGENTA);//����һ�����ڣ�д��ָ��������ɫ
	
		HAL_Delay(1000);

		LCD_Clear(WHITE);
	
	    Draw_Test();//��ͼ��������
	
		HAL_Delay(300);//��ʱ
		LCD_Clear(BLACK);
		HAL_Delay(300);//��ʱ
		LCD_Clear(RED);
		HAL_Delay(300);//��ʱ
		LCD_Clear(YELLOW);
		HAL_Delay(300);//��ʱ
		LCD_Clear(GREEN);
		HAL_Delay(300);//��ʱ
		LCD_Clear(BLUE);
		HAL_Delay(300);//��ʱ

}


uint16_t D_Color=BLUE; //������ɫ
uint16_t B_Color=WHITE; //������ɫ

//****************************************************************************************/
//������void Font_Test(void)
//��������: ����������ʾ����
/****************************************************************************************/

void Font_Test(void)
{
	LCD_Clear(WHITE);
	Draw_Font16B(8,16,BLUE,"2:������ʾ����");

	HAL_Delay(1000);
	LCD_Clear(WHITE);

	Draw_Font16B(4,20,RED,"0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz");

	HAL_Delay(1000);	
	
	LCD_Clear(WHITE);


}


//****************************************************************************************/
//������void Demo_Menu(void)
//��������: ��ʾ����˵�
/****************************************************************************************/

void Demo_Menu(void)
{

	LCD_Clear(WHITE); //����
	

	Draw_Font24B(4,30,RED,"Һ��������");

	Draw_Font16B(4,60,BLUE,"1: ��ɫ���");

	Draw_Font16B(4,80,BLUE,"2: ������ʾ");

	Draw_Font16B(4,100,BLUE,"3: ͼƬ��ʾ");

	Draw_Font16B(4,120,RED,"hello world");
	Draw_Font16B(4,140,RED,"yyds");

	HAL_Delay(2000);//��ʱ
		
	Color_Test();       //��ɫ������
    Font_Test();        //����������ʾ����
//    GBK_LibFont_Test(); //GBK�ֿ���� -(���ʹ�ò����ֿ��Һ�����汾���˴��������Σ������ֿ���ԣ�
// 	Show_Picture();     //��ʾһ��ͼƬ
}
