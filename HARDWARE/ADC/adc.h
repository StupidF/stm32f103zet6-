#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"



void Adc_Init(void);//ADC��ʼ��
uint16_t  Get_Adc(uint8_t channel);//ADC����
uint16_t  Get_Adc_Average(uint8_t channel, uint8_t times);//ADCƽ��ֵ


#endif 
