#ifndef __LED_H
#define __LED_H
#include "sys.h"//包含系统头文件

#define  LED0     PBout(5)//LED0-->PB5
#define  LED1     PEout(5)//LED1-->PE5

#define  L1       8       //定义8端口为L1
#define  L2       9       //定义9端口为L2
#define  L3       10      //定义10端口为L3
#define  L4       11      //定义11端口为L4

#define  LED(x)   PEout(x)//定义一个参数宏

void LED_Init(void);//声明LED初始化函数




#endif


