#include "led.h"
/***************************************************
* 函数:LED_Init
* 参数:无参
* 返回值:无返回值
* 功能: LED0-->PB5       LED1-->PE5
*       LED(L1)-->PE8    LED(L2)-->PE9  
*       LED(L2)-->PE10   LED(L4)-->PE11  
***************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能PB口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//PB5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//最大速度50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化PB口
	
	GPIO_SetBits(GPIOB, GPIO_Pin_5);//PB5输出高
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//使能PE口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 ;//PE5、PE8、PE9、PE10、PE11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//最大速度50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化PE口
	
	GPIO_SetBits(GPIOE, GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11);//PE5、PE8、PE9、PE10、PE11输出高
}
