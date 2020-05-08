#include "sys.h"
#include "usart.h"		
#include "delay.h"
#include "led.h"
#include "oled.h"
#include "adc.h"
#include "servo.h"
#include "timer.h"
/***************************************************
* Project: 
* Function: 
* Auther:
* Date: 2018/12/23
* Note:电位器PA5--(ADC12_IN5)
***************************************************/
uint16_t t = 0;	
uint16_t adc_value, servo_angle;
int main(void)
{
	SystemInit();//系统初始化
	delay_init();//延时初始化
	uart_init(9600);//串口1初始化
	LED_Init();//LED初始化
	Adc_Init();//ADC初始化
	Timer4_Init(200, 7200);//定时器4初始化
	OLED_Init();//OLED显示屏初始化
	OLED_Clear();//OLED清屏
	OLED_Static_Display();//OLED固定显示
	while(1)
	{	
		
		adc_value = Get_Adc_Average(ADC_Channel_5, 10);//得到ADC的测量值
		servo_angle = (uint16_t)((180.0 / 4095) * 4000);//得到舵机角度	
        Servo_Control(servo_angle);//舵机控制
		OLED_Sport_Display(adc_value, servo_angle);//OLED显示得到的ADC的值和ADC的电压值
		if(t++ / 1000)
		{
			LED0 = 0;
		}
		if(t++ / 2000)
		{
			LED0 = 1;
			t = 0;			
		}
	}
}





