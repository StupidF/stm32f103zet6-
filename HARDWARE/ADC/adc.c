 #include "adc.h"
 #include "delay.h"	   
/***************************************************
* ����:Adc_Init
* ����:�޲�
* ����ֵ:�޷���ֵ
* ����: ���Թ���ͨ��Ϊ�������ǽ�����ͨ��5
***************************************************/													   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����4 72M/4=12,ADC���ʱ�䲻�ܳ���14M

	//PA5��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADC_DeInit(ADC1);  //��λADC1 
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_55Cycles5 );//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_Cmd(ADC1, ENABLE);//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);//ʹ�ܸ�λУ׼  
	
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1)); //�ȴ�У׼����
			
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	//ʹ��ָ����ADC1�����ת����������	
}
/***************************************************
* ����:Get_Adc
* ����:channel-ͨ��ֵ(ͨ��ֵ 5)
* ����ֵ:�������һ��ADC1�������ת�����
* ����: ���ADCֵ,channel:ͨ��ֵ 5
***************************************************/
uint16_t Get_Adc(uint8_t channel)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			     
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	//ʹ��ָ����ADC1�����ת����������		 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1);//�������һ��ADC1�������ת�����
}
/***************************************************
* ����:Get_Adc_Average
* ����:channel-ͨ��ֵ(ͨ��ֵ 5) times-����
* ����ֵ:�������һ��ADC1�������ת�����
* ����: �ɼ�t�Σ�ȡ�ɼ�ƽ��ֵ
***************************************************/
uint16_t Get_Adc_Average(uint8_t channel, uint8_t times)
{
	uint32_t temp_val = 0;
	uint8_t t;
	for(t = 0; t < times; t++)
	{
		temp_val += Get_Adc(channel);//����ƽ��ֵ
		delay_ms(1);
	}
	return temp_val / times;//����AD�ɼ�ƽ��ֵ
} 	 











