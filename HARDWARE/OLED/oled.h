//////////////////////////////////////////////////////////////////////////////////	 
//
//  �� �� ��   : oled.h
//  �� �� ��   : v2.0
//  ��    ��   : Evk123
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : 0.69��OLED �ӿ���ʾ����(STM32F103ZEϵ��IIC)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND   ��Դ��
//              VCC   ��5V��3.3v��Դ
//              SCL   ��PB6��SCL��
//              SDA   ��PB7��SDA��            
//              ----------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////
#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	    	
#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED IIC�˿ڶ���----------------  					   

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB, GPIO_Pin_6)//SCL
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB, GPIO_Pin_6)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB, GPIO_Pin_7)//SDA
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB, GPIO_Pin_7)

 		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����


//OLED�����ú���
void OLED_WR_Byte(unsigned char dat, unsigned char cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(unsigned char x, unsigned char y, unsigned char t);
void OLED_Fill(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char dot);
void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char chr, unsigned char Char_Size);
void OLED_ShowNum(unsigned char x, unsigned char y, u32 num, unsigned char len, unsigned char size);
void OLED_ShowString(unsigned char x, unsigned char y, unsigned char *p, unsigned char Char_Size);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowChinese(unsigned char x, unsigned char y, unsigned char no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
//void Delay_50ms(unsigned int Del_50ms);
//void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void IIC_Start(void);
void IIC_Stop(void);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void IIC_Wait_Ack(void);
void distance_display(void);

void OLED_Static_Display(void);//��̬��ʾ
void OLED_Sport_Display(uint16_t adc_value, uint16_t servo_angle);//��̬��ʾ

void OLED_Display_RealDate(uint32_t year, uint8_t month ,uint8_t date ,uint8_t week);
void OLED_Display_RealTime(uint8_t hour, uint8_t minute, uint8_t second);
#endif  
	 



