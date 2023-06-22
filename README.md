# STM32G431CBT6-Mini-Board
## 更新说明

## 适用芯片
STM32G431CBT6<br>
``` 注意：理论上支持其他LQPF48封装的芯片，但未经验证。```
<br>

## 本工程包含的内容
1. 原理图及PCB文件
2. HAL库工程模板
3. 寄存器工程模板

## PCB图片
![正面](https://github.com/Harvey8665/STM32G431CBT6-Mini-Board/blob/master/picture/zhengmian.png)<br>
![反面](https://github.com/Harvey8665/STM32G431CBT6-Mini-Board/blob/master/picture/beimian.png)<br>
<br>

## HAL库工程模板
默认功能：LED1每500ms闪烁一次<br>
有待优化的地方：可更换为HAL_GPIO_ToglePin函数，但是本工程加入该函数会提示未定义该函数（目前暂无解决办法）
```2023年6月22日更新：已验证完成，可以正常使用```<br>
在使用CubeMX生成时，会提示存在错误，这是因为CubeMX生成工程时缺少启动文件（目前已手动添加）。<br>
CubeMX生成工程时提示以下错误，点击OK即可完成。<br>
![CubeMX报错](https://github.com/Harvey8665/STM32G431CBT6-Mini-Board/blob/master/picture/Cube_MX_Error.png)<br>
默认编译软件：MDK5.38 AC5<br>

## 寄存器工程模板
1、新建工程模板<br>
2、上电后LED亮<br>
3、计划更新延时函数<br>
```2023年6月22日更新：已验证完成，可以正常使用```<br>
默认编译软件：MDK5.38 AC5<br>