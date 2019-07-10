#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "adc.h"

//ALIENTEK Mini STM32�����巶������15
//ADCʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
   	
 int main(void)
 { 
	u16 adcx;
	int i;
	float temp;
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	Adc_Init();		  		//ADC��ʼ��	    
	
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
