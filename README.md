# STM32G431CBT6-Mini-Board
## 更新说明

## 适用芯片
STM32G431CBT6<br>
``` 注意：理论上支持其他LQPF48封装的芯片，但未经验证。```
<br>

## 本工程计划更新的内容
1. 原理图及PCB文件（2023年6月18日已更新）
2. HAL库工程模板（2023年6月19日已更新，未实际验证）
3. 寄存器工程模板（2023年6月20日已更新，未实际验证）

## PCB图片
![正面](https://github.com/Harvey8665/STM32G431CBT6-Mini-Board/blob/master/picture/zhengmian.png)<br>
![反面](https://github.com/Harvey8665/STM32G431CBT6-Mini-Board/blob/master/picture/beimian.png)<br>
<br>

## HAL库工程模板
默认功能：点亮LED灯<br>
```注意：该工程未上开发板测试，如不能使用，请新增issues```<br>
在使用CubeMX生成时，会提示存在错误，这是因为CubeMX生成工程时缺少启动文件（目前已手动添加）。<br>
默认编译软件：MDK5.38 AC6<br>

## 寄存器工程模板
1、新建工程模板<br>
2、上电后LED亮<br>
3、计划更新延时函数<br>
```注意：该工程未上开发板测试，如不能使用，请新增issues```<br>
默认编译软件：MDK5.38 AC5<br>