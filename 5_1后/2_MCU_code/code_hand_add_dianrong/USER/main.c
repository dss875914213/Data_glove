#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "adc.h"
#include "myiic.h"
#include "ad7746.h"

//ALIENTEK Mini STM32�����巶������15
//ADCʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
   	
 int main(void)
 { 
	u16 adcx;
	int i;
	float temp;
	int cap_temp;
	float cap = 0.0;
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	Adc_Init();		  		//ADC��ʼ��	  
	IIC_Init();
	
	CDC_WRREG(0x08,0x01);	//�رյ�ѹת��
	CDC_WRREG(0x09,0x1b);	//���ü���ԴEXCA��EXCB,��EXCB���ó�EXCA�ĵ���
	CDC_WRREG(0x0A,0x09);	//����ת��ģʽ��ת��ʱ������������
	
	CDC_WRREG(0x0B,0xff);	//CAPDAC����
	CDC_WRREG(0x0C,0xe2);	//CAPDAC���ã�0x0B - 0x0C = 0xff - 0xe2 -->0~100pF
	CDC_WRREG(0x07,0x80);	//ѡ�����ת��ͨ����0x80:��1��2,0xc0:��1��2	 
	
	while(1)
	{	
		//����
		for(i=0;i<12;i++)
		{
			adcx=Get_Adc_Average(ADC_Channel_0+i,4);
			temp=(float)adcx*(3.3/4096);
			printf("%d %f\r\n",i,temp);
		}
		
		//����
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
