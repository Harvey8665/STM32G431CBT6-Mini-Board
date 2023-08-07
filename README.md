# STM32G431CBT6-Mini-Board
## 更新说明
### 2023/8/7 14：48
将寄存器工程的相关头文件添加到工程中<br>
### 2023/7/27 19：30
将寄存器工程修改为ARM Compiler Version 6编译<br>
### 2023/7/16 14：30
更新HAL库的屏幕驱动程序<br>
### 2023/7/7 14：16
1、优化寄存器版本工程<br>
2、新增delay.c、delay.其中包含延时函数<br>
### 2023/6/25 10：09
1、优化HAL库版本工程<br>
2、去除本地路径中的中文<br>
3、解决了CubeMX生成代码时报错的问题<br>
4、将HAL库工程修改为ARM Compiler Version 6编译<br>
### 2023/6/22 15：27
更新第一个完整版本。<br>

## 本工程包含的内容
1. 原理图<br>
2. HAL库工程模板（HAL_Project文件夹）<br>
3. 寄存器工程模板（Register_Project文件夹）<br>
4. PCB文件请到立创开源硬件平台[
STM32G431CBT6最小系统板](https://oshwhub.com/dc123456/stm32g431cbt6-zui-xiao-xi-tong-ban)查看<br>

## 适用芯片
STM32G431CBT6（硬件软件均支持）<br>
STM32G431C6、STM32G431C8、STM32G474CB、STM32G474CC、STM32G474CE（仅硬件支持，软件需要重新建工程）<br>
``` 注意：理论上支持其他LQPF48封装的STM32G4系列芯片，但未经验证。```
<br>

## 注意事项
### 一、使用LCD屏幕前需要做的工作(HAL库)
由于LCD屏幕占用资源过多，在主程序中已将相关设置移除，如果需要重新使用LCD，则需要做以下工作。<br>
由于图片占用空间较多，故已移除了显示图片的相关内容，如需恢复，请按步骤5恢复
#### 1、将驱动文件.c添加到project中
如下图所示，将以下c文件添加到project中。<br>
![C文件添加到project中](https://github.com/Harvey8665/STM32G431CBT6-Mini-Board/blob/master/picture/project.png)<br>
`Dis_Picture.c`包含了显示图片的函数，`Picture.c`包含了图片信息，如果没用到这两个文件，建议不用添加到项目，以免占用过多的flash<br>
#### 2、设置硬件SPI2
按照下面三张图设置SPI2。<br>
![SPI2设置1](https://github.com/Harvey8665/STM32G431CBT6-Mini-Board/blob/master/picture/spi21.png)<br>
![SPI2设置2](https://github.com/Harvey8665/STM32G431CBT6-Mini-Board/blob/master/picture/spi22.png)<br>
![SPI2设置3](https://github.com/Harvey8665/STM32G431CBT6-Mini-Board/blob/master/picture/spi23.png)<br>
#### 3、设置其他GPIO引脚
如下图所示，初始化PB11、PB12、PB14引脚。<br>
![GPIO设置](https://github.com/Harvey8665/STM32G431CBT6-Mini-Board/blob/master/picture/gpio.png)<br>
设置完成后点击“GENERATE CODE”生成代码<br>
#### 4、取消掉以下代码的注释
将引用头文件、初始化lcd的代码取消注释。<br>
`注意：使用/* */注释的内容仅用于定位代码所在的位置，不要修改这部分注释`<br>
```
/* USER CODE BEGIN Includes */
//#include "lcd.h"      //1.8寸LCD屏幕
/* USER CODE END Includes */

/* USER CODE BEGIN 2 */
//  // *------------LCD初始化-----------------//
//  // *--LCD驱动内容占用资源较多，请谨慎使用---//
//  LCD_Init();
//  LCD_Clear(WHITE);
//  Show_Picture();
//  // *-------------------------------------//
/* USER CODE END 2 */
```
#### 5、显示图片的方法（选做）
在完成以上4个步骤之后，将`Dis_Picture.c`和`Picture.c`添加到project中，同时在`lcd.h`中取消`Dis_Picture.h`的注释<br>
```
///////////////////////////加入项目的关联头文件////////////////////////////////////

#include "main.h"
#include "stdlib.h"
#include "spi.h"
#include "font.h"
#include "Text.h"
//#include "Dis_Picture.h"  //如需显示图片，请取消这行代码的注释
```
### 二、I2C协议的OLED使用硬件I2C驱动的配置(HAL库)
#### 1、将驱动文件`oled.c`添加到project中
#### 2、设置硬件I2C
按下图方式设置硬件I2C，设置完成后点击`GENERATE CODE`生成代码<br>
![I2C设置1](https://github.com/Harvey8665/STM32G431CBT6-Mini-Board/blob/master/picture/i2c31.png)<br>
![I2C设置2](https://github.com/Harvey8665/STM32G431CBT6-Mini-Board/blob/master/picture/i2c32.png)<br>
#### 3、在main.c中添加代码
在main.c中添加以下代码，其中`OLED_Init`函数已经包含了0x78和0x7A地址的初始化<br>
`注意：使用/* */注释的内容仅用于定位代码所在的位置，不要修改这部分注释`<br>
```
  /* USER CODE BEGIN Includes */
  #include "oled.h"     //0.96寸OLED屏幕
  /* USER CODE END Includes */

  /* USER CODE BEGIN 2 */
  // *--------------OLED初始化--------------//
  OLED_Init();  // * oled初始化
  OLED_ClearRAM();
  OLED_ClearRAM2();
  OLED_ShowStr(0,0,"OLED is OK",2);
  OLED_ShowStr2(0,0,"OLED is OK",2);
  OLED_RefreshRAM();    // * oled flash
  OLED_RefreshRAM2();    // * oled flash
  OLED_ClearRAM();
  OLED_ClearRAM2();
  // *--------------------------------------//
  /* USER CODE END 2 */
```

## STM32G431CBT6简介
![简介](https://github.com/Harvey8665/STM32G431CBT6-Mini-Board/blob/master/picture/stm32g431cb.jpg)<br>

## HAL库工程模板
默认功能：LED1每500ms闪烁一次<br>
有待优化的地方：可更换为HAL_GPIO_ToglePin函数，但是本工程加入该函数会提示未定义该函数（目前暂无解决办法）<br>
```2023年6月22日更新：已验证完成，可以正常使用```<br>
在使用CubeMX生成时，会提示存在错误，这是因为包含了本地文件夹路径包含了中文（2023/06/25 已修改）。<br>
CubeMX生成工程时如果提示以下错误，点击OK即可完成（但此时使用AC6编译可能会报错）。<br>
![CubeMX报错](https://github.com/Harvey8665/STM32G431CBT6-Mini-Board/blob/master/picture/Cube_MX_Error.png)<br>
默认编译软件：MDK5.38 AC6<br>

## 寄存器工程模板
1、新建工程模板<br>
2、上电后LED闪烁（每500ms变换一次电平）<br>
3、包含微秒、毫秒、秒延时函数<br>
```2023年6月22日更新：已验证完成，可以正常使用```<br>
默认编译软件：MDK5.38 AC6<br>

