#include "Dis_Picture.h"


//////////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
//图片显示 驱动代码
/******************************************************************************/


//16位 垂直扫描  右到左  高位在前
void Show_Picture(void)
{
    uint32_t i,j,k=0;

    uint16_t picH,picL;

    LCD_Clear(WHITE);//清屏

    Draw_Font16B(4,16,RED,"3:picture test");

    HAL_Delay(1000);    //延时显示

    LCD_Clear(WHITE);  //清屏

    {

        LCD_Set_Window(0,0,lcddev.width,lcddev.height);//设置一个自动换行显示区域窗口

        LCD_WriteRAM_Prepare();     	//开始写入GRAM

        for(i=0;i<lcddev.height;i++)
            for(j=0;j<lcddev.width;j++)
            {
                picH=gImage_LCD180[k++];
                picL=gImage_LCD180[k++];

                LCD_WR_DATA8(picH);  //写8位显示数据
                LCD_WR_DATA8(picL);

            }
    }

    HAL_Delay(2000);    //延时显示

}
