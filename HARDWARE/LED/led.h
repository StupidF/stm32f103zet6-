#ifndef __LED_H
#define __LED_H
#include "sys.h"//����ϵͳͷ�ļ�

#define  LED0     PBout(5)//LED0-->PB5
#define  LED1     PEout(5)//LED1-->PE5

#define  L1       8       //����8�˿�ΪL1
#define  L2       9       //����9�˿�ΪL2
#define  L3       10      //����10�˿�ΪL3
#define  L4       11      //����11�˿�ΪL4

#define  LED(x)   PEout(x)//����һ��������

void LED_Init(void);//����LED��ʼ������




#endif


