//////////////////////////////////////////////////////////////////////////////////	 
//
//  ÎÄ ¼þ Ãû   : main.c
//  °æ ±¾ ºÅ   : v2.0
//  ×÷    Õß   : Evk123
//  Éú³ÉÈÕÆÚ   : 2014-0101
//  ×î½üÐÞ¸Ä   : 
//  ¹¦ÄÜÃèÊö   : 0.69´çOLED ½Ó¿ÚÑÝÊ¾Àý³Ì(STM32F103ZEÏµÁÐIIC)
//              ËµÃ÷: 
//              ----------------------------------------------------------------
//              GND   µçÔ´µØ
//              VCC   ½Ó5V»ò3.3vµçÔ´
//              SCL   ½ÓPB6£¨SCL£©
//              SDA   ½ÓPB7£¨SDA£©            
//              ----------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////£

#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  
#include "bmp.h"
#include "delay.h"

//OLEDµÄÏÔ´æ
//´æ·Å¸ñÊ½ÈçÏÂ.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   
/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{
	OLED_SCLK_Set() ;
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

/**********************************************
* IIC Stop
**********************************************/
void IIC_Stop()
{
	OLED_SCLK_Set();
//	OLED_SCLK_Clr();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();	
}

void IIC_Wait_Ack()
{
	OLED_SCLK_Set();
	OLED_SCLK_Clr();
}
/**********************************************
* IIC Write byte
**********************************************/

void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da = IIC_Byte;
	OLED_SCLK_Clr();
	for(i = 0; i < 8; i++)		
	{		
		m = da;
		// 	OLED_SCLK_Clr();
		m &= 0x80;
		if(m == 0x80)
			OLED_SDIN_Set();	
		else 
			OLED_SDIN_Clr();
		da = da << 1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();	
	}


}
/**********************************************
* IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{   
	IIC_Start();
    Write_IIC_Byte(0x78);            //Slave address,SA0=0
	IIC_Wait_Ack();	
    Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
    Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
    IIC_Stop();
}
/**********************************************
* IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{   
	IIC_Start();   
	Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	   
	Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	   
	Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
	IIC_Stop();
}
/**********************************************
* OLED WR Byte
**********************************************/
void OLED_WR_Byte(unsigned char dat, unsigned char cmd)
{
	if(cmd)		 
		Write_IIC_Data(dat);	
	else      				
		Write_IIC_Command(dat);	
}


/********************************************
* fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m = 0; m < 8; m++)
	{
		OLED_WR_Byte(0xb0 + m, 0);		//page0-page1
		OLED_WR_Byte(0x00, 0);		//low column start address
		OLED_WR_Byte(0x10, 0);		//high column start address
		for(n = 0; n < 128; n++)							
			OLED_WR_Byte(fill_Data,1);			
	}
}

/********************************************
* Delay 50ms
********************************************/
void Delay_50ms(unsigned int Del_50ms)
{	
	unsigned int m;
	for(; Del_50ms > 0; Del_50ms--)		
	for(m = 6245; m > 0; m--);
}
/********************************************
* Delay 1ms
********************************************/
void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j = 0; j < 123; j++);
	}
}

/********************************************
* ×ø±êÉèÖÃ
********************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	
	OLED_WR_Byte(0xb0 + y,OLED_CMD);
	OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
	OLED_WR_Byte((x & 0x0f), OLED_CMD); 
}   	  
/********************************************
* ¿ªÆôOLEDÏÔÊ¾
********************************************/     
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D, OLED_CMD);  //SET DCDCÃüÁî
	OLED_WR_Byte(0X14, OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF, OLED_CMD);  //DISPLAY ON
}
/********************************************
* ¹Ø±ÕOLEDÏÔÊ¾  
********************************************/       
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D, OLED_CMD);  //SET DCDCÃüÁî
	OLED_WR_Byte(0X10, OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE, OLED_CMD);  //DISPLAY OFF
}		   			 
/********************************************
* ÇåÆÁº¯Êý(ÇåÍêÆÁ,Õû¸öÆÁÄ»ÊÇºÚÉ«µÄ!ºÍÃ»µãÁÁÒ»Ñù)
********************************************/	  
void OLED_Clear(void)  
{  
	unsigned char i,n;		    
	for(i = 0; i < 8; i++)  
	{  
		OLED_WR_Byte(0xb0 + i, OLED_CMD);    //ÉèÖÃÒ³µØÖ·£¨0~7£©
		OLED_WR_Byte(0x00, OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁÐµÍµØÖ·
		OLED_WR_Byte(0x10, OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁÐ¸ßµØÖ·   
		for(n = 0; n < 128; n++)
			OLED_WR_Byte(0, OLED_DATA); 
	} //¸üÐÂÏÔÊ¾
}
/********************************************
* OLED On
********************************************/
void OLED_On(void)  
{  
	unsigned char i,n;		    
	for(i = 0; i < 8; i++)  
	{  
		OLED_WR_Byte(0xb0 + i, OLED_CMD);    //ÉèÖÃÒ³µØÖ·£¨0~7£©
		OLED_WR_Byte(0x00, OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁÐµÍµØÖ·
		OLED_WR_Byte(0x10, OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁÐ¸ßµØÖ·   
		for(n = 0; n < 128; n++)
			OLED_WR_Byte(1, OLED_DATA); 
	} //¸üÐÂÏÔÊ¾
}
/********************************************
* OLED_ShowChar
* x:0~127   y:0~63
* Char_Size:Ñ¡Ôñ×ÖÌå 16/12 
* ×ÖÌåÎª16Ê±£¬ÐÐÏÔÊ¾0~15×Ö·û£¬ÁÐÏÔÊ¾0~6£¨0 2 4 6£©4ÐÐ
* ×ÖÌåÎª12Ê±£¬ÐÐÏÔÊ¾0~15×Ö·û£¬ÁÐÏÔÊ¾0~7£¨0 1 2 3 4 5 6 7£©8ÐÐ
********************************************/
void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char chr, unsigned char Char_Size)
{      	
	unsigned char c = 0,i = 0;		
	c = chr - ' ';//µÃµ½Æ«ÒÆºóµÄÖµ				
	if(x > Max_Column - 1)
	{
		x = 0;
		y = y + 2;
	}	
	if(Char_Size == 16)
	{
		OLED_Set_Pos(x, y);	
		for(i = 0; i < 8; i++)
			OLED_WR_Byte(F8X16[c * 16 + i], OLED_DATA);
		OLED_Set_Pos(x, y + 1);
		for(i = 0; i < 8; i++)
			OLED_WR_Byte(F8X16[c * 16 + i + 8], OLED_DATA);
	}
	else 	
	{	
		OLED_Set_Pos(x, y);
		for(i = 0; i < 6; i++)
			OLED_WR_Byte(F6x8[c][i], OLED_DATA);
		
	}
}
/********************************************
* oled pow     m^nº¯Êý
********************************************/
u32 oled_pow(unsigned char m,unsigned char n)
{
	u32 result = 1;	 
	while(n--)
		result *= m;    
	return result;
}				  
/********************************************
* ÏÔÊ¾Êý×Ö
* x,y : Æðµã×ø±ê	 
* len : Êý×ÖµÄÎ»Êý
* size: ×ÖÌå´óÐ¡
// mode: Ä£Ê½	0,Ìî³äÄ£Ê½;1,µþ¼ÓÄ£Ê½
* num: ÊýÖµ(0~4294967295);
********************************************/		   		  
void OLED_ShowNum(unsigned char x,unsigned char y,u32 num,unsigned char len,unsigned char size2)
{         	
	unsigned char t,temp;
	unsigned char enshow = 0;						   
	for(t = 0; t < len; t++)
	{
		temp = (num / oled_pow(10, len - t - 1)) % 10;
		if(enshow == 0 && t < (len - 1))
		{
			if(temp == 0)
			{
				OLED_ShowChar(x + (size2 / 2) * t, y, ' ', size2);
				continue;
			}
			else 
				enshow = 1;  	 
		}
	 	OLED_ShowChar(x + (size2 / 2) * t, y, temp + '0', size2); 
	}
} 
/********************************************
* OLED ShowString
********************************************/
void OLED_ShowString(unsigned char x, unsigned char y, unsigned char *chr, unsigned char Char_Size)
{
	unsigned char j = 0;
	while (chr[j] != '\0')
	{		
		OLED_ShowChar(x, y, chr[j], Char_Size);		
		x += 8;
		if(x > 120)
		{
			x = 0;
			y += 2;
		}	
		j++;
	}
}
/********************************************
* OLED ShowChinese
********************************************/
void OLED_ShowChinese(unsigned char x, unsigned char y, unsigned char no)
{      			    
	unsigned char t, adder = 0;
	OLED_Set_Pos(x, y);	
    for(t = 0;t < 16;t++)	
	{	
		OLED_WR_Byte(Hzk[2 * no][t], OLED_DATA);
		adder += 1;  
	}		
	OLED_Set_Pos(x, y + 1);	
    for(t = 0; t < 16; t++)		
	{	
		OLED_WR_Byte(Hzk[2 * no + 1][t], OLED_DATA);
		adder += 1;     
	}					
}
/********************************************
* ¹¦ÄÜÃèÊö£ºÏÔÊ¾ÏÔÊ¾BMPÍ¼Æ¬128¡Á64ÆðÊ¼µã×ø±ê(x,y),xµÄ·¶Î§0¡«127£¬yÎªÒ³µÄ·¶Î§0¡«7
********************************************/	
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[])
{ 	
	unsigned int j = 0;
	unsigned char x, y;  
	if(y1 % 8 == 0) 	 
		y = y1 / 8;      
	else   
		y = y1 / 8 + 1;	
	for(y = y0; y < y1; y++)	
	{		
		OLED_Set_Pos(x0, y);		 
		for(x = x0; x < x1; x++)				
			OLED_WR_Byte(BMP[j++], OLED_DATA);	    		
	}
} 
/********************************************
* ³õÊ¼»¯SSD1306	
********************************************/					    
void OLED_Init(void)
{ 	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //Ê¹ÄÜB¶Ë¿ÚÊ±ÖÓ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //ÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//ËÙ¶È50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //³õÊ¼»¯GPIOB6,7
 	GPIO_SetBits(GPIOB, GPIO_Pin_6 | GPIO_Pin_7);	
	
    delay_ms(800);
	
    OLED_WR_Byte(0xAE, OLED_CMD);//--display off
	OLED_WR_Byte(0x00, OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10, OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40, OLED_CMD);//--set start line address  
	OLED_WR_Byte(0xB0, OLED_CMD);//--set page address
	OLED_WR_Byte(0x81, OLED_CMD); // contract control
	OLED_WR_Byte(0xFF, OLED_CMD);//--128   
	OLED_WR_Byte(0xA1, OLED_CMD);//set segment remap 
	OLED_WR_Byte(0xA6, OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8, OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F, OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8, OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3, OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00, OLED_CMD);//
	
	OLED_WR_Byte(0xD5, OLED_CMD);//set osc division
	OLED_WR_Byte(0x80, OLED_CMD);//
	
	OLED_WR_Byte(0xD8, OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05, OLED_CMD);//
	
	OLED_WR_Byte(0xD9, OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1, OLED_CMD);//
	
	OLED_WR_Byte(0xDA, OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12, OLED_CMD);//
	
	OLED_WR_Byte(0xDB, OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30, OLED_CMD);//
	
	OLED_WR_Byte(0x8D, OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14, OLED_CMD);//
	
	OLED_WR_Byte(0xAF, OLED_CMD);//--turn on oled panel
}  

/*********************************************************
* --------------0.96´çOLED¾²Ì¬ÏÔÊ¾º¯Êý--------------------
* º¯Êý£ºOLED_Static_Display
* º¯Êý²ÎÊý£ºÎÞ²ÎÊý
* ±¸×¢£ºOLED¹Ì¶¨ÏÔÊ¾
************************************************************/
void OLED_Static_Display(void)
{
	OLED_ShowChinese((0 + 2) * 16, 0, 0);//µç
	OLED_ShowChinese((1 + 2) * 16, 0, 1);//×Ó
	OLED_ShowChinese((2 + 2) * 16, 0, 2);//Éç
	OLED_ShowChinese((3 + 2) * 16, 0, 3);//Çø
	OLED_ShowString(0, 2, (uint8_t *)"****ADC-TEST****", 16);
	OLED_ShowString(0, 4, (uint8_t *)"ADC_VALUE:", 16);
	OLED_ShowString(0, 6, (uint8_t *)"SERVO_ANGLE:", 16);
}
/*********************************************************
* --------------0.96´çOLED¶¯Ì¬ÏÔÊ¾º¯Êý--------------------
* º¯Êý£ºOLED_Sport_Display
* º¯Êý²ÎÊý£ºÎÞ²ÎÊý
* ±¸×¢£ºOLED¹Ì¶¨ÏÔÊ¾
************************************************************/
void OLED_Sport_Display(uint16_t adc_value, uint16_t servo_angle)
{
	uint8_t adc[5], angle[4];
	
	adc[0] = adc_value / 1000 % 10 + '0';
	adc[1] = adc_value / 100 % 10 + '0';
	adc[2] = adc_value / 10 % 10 + '0';
	adc[3] = adc_value % 10 + '0';
	adc[4] = '\0';
	OLED_ShowString(10 * 8, 4, adc,16);//ÏÔÊ¾ADCµÄ²âÁ¿Öµ
	
	
	angle[0] = servo_angle / 100 % 10 + '0';
	angle[1] = servo_angle / 10 % 10 + '0';
	angle[2] = servo_angle % 10 + '0';
	angle[3] = '\0';
	OLED_ShowString(12 * 8, 6, angle,16);//ÏÔÊ¾¶æ»ú½Ç¶È
}
/**********************************************************************
* º¯Êý£ºÊµÊ±ÈÕÆÚÏÔÊ¾º¯Êý
* ²ÎÊý£ºÄêÔÂÈÕ
* ¹¦ÄÜ£º
* ±¸×¢£º  
*    2018-08-21
*    Tuesday
***********************************************************************/	
void OLED_Display_RealDate(uint32_t year, uint8_t month ,uint8_t date ,uint8_t week)
{
	static uint8_t date_str[17];

	date_str[0] = ' ';
	date_str[1] = ' '; 
	date_str[2] = ' '; 
	date_str[3] = year / 1000  % 10 + '0';//Äê	
	date_str[4] = year / 100 % 10 + '0';
	date_str[5] = year / 10 % 10 + '0';
    date_str[6] = year % 10 + '0';
	
	date_str[7] = '-';
	date_str[8] = month /10 % 10 + '0';//ÔÂ
	date_str[9] = month % 10 + '0';
	
	date_str[10] = '-';
	date_str[11] = date / 10 % 10 + '0';//ÈÕ
	date_str[12] = date % 10 + '0';
		
	date_str[13] = ' ';
	date_str[14] = ' '; 
	date_str[15] = ' ';
	date_str[16] = '\0';
	
	OLED_ShowString(0, 2, date_str, 16);//ÏÔÊ¾ÄêÔÂÈÕ
	
	switch(week)//ÏÔÊ¾ÐÇÆÚ
	{
		case 0:
			OLED_ShowString(0, 6, "     Sunday     ", 16);  //ÐÇÆÚÌì
			break;
		case 1:
			OLED_ShowString(0, 6, "     Monday     ", 16);  //ÐÇÆÚÒ»
			break;
		case 2:
			OLED_ShowString(0, 6, "    Tuesday     ", 16); //ÐÇÆÚ¶þ
			break;
		case 3:
			OLED_ShowString(0, 6, "    Wednesday   ", 16);//ÐÇÆÚÈý
			break;
		case 4:
			OLED_ShowString(0, 6, "    Thursday    ", 16);//ÐÇÆÚËÄ
			break;
		case 5:
			OLED_ShowString(0, 6, "     Friday     ", 16);  //ÐÇÆÚÎå
			break;
		case 6:
			OLED_ShowString(0, 6, "    Saturday    ", 16);//ÐÇÆÚÁù
			break;  
		default:
			break;
	}
}
/**********************************************************************
* º¯Êý£ºÊµÊ±Ê±¼äÏÔÊ¾º¯Êý
* ²ÎÊý£ºÊ±·ÖÃë
* ¹¦ÄÜ£º
* ±¸×¢£º  
*    12:00:20
***********************************************************************/	
void OLED_Display_RealTime(uint8_t hour, uint8_t minute, uint8_t second)
{
	static uint8_t time_str[17];
	time_str[0] = ' ';
	time_str[1] = ' '; 
	time_str[2] = ' '; 
	time_str[3] = ' '; 
	
	time_str[4] = hour / 10 % 10 + '0';//Ê±
	time_str[5] = hour % 10 + '0';
	
	time_str[6] = ':';
	time_str[7] = minute / 10 % 10 + '0';//·Ö
	time_str[8] = minute % 10 + '0';
		
	time_str[9] = ':';
	time_str[10] = second / 10 % 10 + '0';//Ãë
	time_str[11] = second % 10 + '0';
	
	time_str[12] = ' ';
	time_str[13] = ' '; 
	time_str[14] = ' ';
	time_str[15] = ' '; 	
	time_str[16] = '\0';
	
	OLED_ShowString(0, 4, time_str, 16);//ÏÔÊ¾Ê±·ÖÃë
}






