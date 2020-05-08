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
* Note:��λ��PA5--(ADC12_IN5)
***************************************************/
uint16_t t = 0;	
uint16_t adc_value, servo_angle;
int main(void)
{
	SystemInit();//ϵͳ��ʼ��
	delay_init();//��ʱ��ʼ��
	uart_init(9600);//����1��ʼ��
	LED_Init();//LED��ʼ��
	Adc_Init();//ADC��ʼ��
	Timer4_Init(200, 7200);//��ʱ��4��ʼ��
	OLED_Init();//OLED��ʾ����ʼ��
	OLED_Clear();//OLED����
	OLED_Static_Display();//OLED�̶���ʾ
	while(1)
	{	
		
		adc_value = Get_Adc_Average(ADC_Channel_5, 10);//�õ�ADC�Ĳ���ֵ
		servo_angle = (uint16_t)((180.0 / 4095) * 4000);//�õ�����Ƕ�	
        Servo_Control(servo_angle);//�������
		OLED_Sport_Display(adc_value, servo_angle);//OLED��ʾ�õ���ADC��ֵ��ADC�ĵ�ѹֵ
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





