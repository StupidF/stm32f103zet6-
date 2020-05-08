#include "led.h"
/***************************************************
* ����:LED_Init
* ����:�޲�
* ����ֵ:�޷���ֵ
* ����: LED0-->PB5       LED1-->PE5
*       LED(L1)-->PE8    LED(L2)-->PE9  
*       LED(L2)-->PE10   LED(L4)-->PE11  
***************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��PB��ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//PB5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����ٶ�50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��PB��
	
	GPIO_SetBits(GPIOB, GPIO_Pin_5);//PB5�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//ʹ��PE��ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 ;//PE5��PE8��PE9��PE10��PE11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����ٶ�50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��PE��
	
	GPIO_SetBits(GPIOE, GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11);//PE5��PE8��PE9��PE10��PE11�����
}
