#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "adc.h"
#include "myiic.h"
#include "ad7746.h"

//ALIENTEK Mini STM32开发板范例代码15
//ADC实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
   	
 int main(void)
 { 
	u16 adcx;
	int i;
	float temp;
	int cap_temp;
	float cap = 0.0;
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
 	Adc_Init();		  		//ADC初始化	  
	IIC_Init();
	
	CDC_WRREG(0x08,0x01);	//关闭电压转换
	CDC_WRREG(0x09,0x1b);	//配置激励源EXCA和EXCB,将EXCB配置成EXCA的倒数
	CDC_WRREG(0x0A,0x09);	//连续转换模式，转换时间最长，精度最高
	
	CDC_WRREG(0x0B,0xff);	//CAPDAC配置
	CDC_WRREG(0x0C,0xe2);	//CAPDAC配置，0x0B - 0x0C = 0xff - 0xe2 -->0~100pF
	CDC_WRREG(0x07,0x80);	//选择电容转换通道，0x80:开1关2,0xc0:关1开2	 
	
	while(1)
	{	
		//电阻
		for(i=0;i<12;i++)
		{
			adcx=Get_Adc_Average(ADC_Channel_0+i,4);
			temp=(float)adcx*(3.3/4096);
			printf("%d %f\r\n",i,temp);
		}
		
		//电容
		while(1)
		{
			cap_temp = CDC_RDREG(0x00);
			if(cap_temp==0x02)
				break;
		}
		while(1)
		{
			cap_temp = CDC_RDREG(0x00);
			if(cap_temp==0x02)
				break;
		}
		cap = Read_7746data();
		printf("%d %f\r\n",100,temp);
		LED0=!LED0;
		//delay_ms(250);	
		
	}											    
}	
