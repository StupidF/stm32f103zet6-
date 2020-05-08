#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"



void Adc_Init(void);//ADC初始化
uint16_t  Get_Adc(uint8_t channel);//ADC采样
uint16_t  Get_Adc_Average(uint8_t channel, uint8_t times);//ADC平均值


#endif 
