 #include "adc.h"
 #include "delay.h"	   
/***************************************************
* 函数:Adc_Init
* 参数:无参
* 返回值:无返回值
* 功能: 仅以规则通道为例，我们将开启通道5
***************************************************/													   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE );	  //使能ADC1通道时钟
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子4 72M/4=12,ADC最大时间不能超过14M

	//PA5作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADC_DeInit(ADC1);  //复位ADC1 
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_55Cycles5 );//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_Cmd(ADC1, ENABLE);//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);//使能复位校准  
	
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1)); //等待校准结束
			
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	//使能指定的ADC1的软件转换启动功能	
}
/***************************************************
* 函数:Get_Adc
* 参数:channel-通道值(通道值 5)
* 返回值:返回最近一次ADC1规则组的转换结果
* 功能: 获得ADC值,channel:通道值 5
***************************************************/
uint16_t Get_Adc(uint8_t channel)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			     
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	//使能指定的ADC1的软件转换启动功能		 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));//等待转换结束
	return ADC_GetConversionValue(ADC1);//返回最近一次ADC1规则组的转换结果
}
/***************************************************
* 函数:Get_Adc_Average
* 参数:channel-通道值(通道值 5) times-次数
* 返回值:返回最近一次ADC1规则组的转换结果
* 功能: 采集t次，取采集平均值
***************************************************/
uint16_t Get_Adc_Average(uint8_t channel, uint8_t times)
{
	uint32_t temp_val = 0;
	uint8_t t;
	for(t = 0; t < times; t++)
	{
		temp_val += Get_Adc(channel);//叠加平均值
		delay_ms(1);
	}
	return temp_val / times;//返回AD采集平均值
} 	 











