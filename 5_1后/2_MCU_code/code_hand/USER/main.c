#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "adc.h"

//ALIENTEK Mini STM32开发板范例代码15
//ADC实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
   	
 int main(void)
 { 
	u16 adcx;
	int i;
	float temp;
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
 	Adc_Init();		  		//ADC初始化	    
	
	while(1)
	{
		for(i=0;i<12;i++)
		{
			adcx=Get_Adc_Average(ADC_Channel_0+i,4);
			temp=(float)adcx*(3.3/4096);
			printf("%d %f\r\n",i,temp);
		}

		LED0=!LED0;
		//delay_ms(250);	
		
	}											    
}	
