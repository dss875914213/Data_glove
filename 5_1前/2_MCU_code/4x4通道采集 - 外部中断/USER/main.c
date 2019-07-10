#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"  
#include "24cxx.h" 
#include "myiic.h"
#include "ad7746.h"
#include "exti.h"

//u8 temp = 0,tempdata = 0;
//u8 channeli = 0,channelj = 0;

//u8 width = 0;
//float cap = 0.0;
   	
 int main(void)
 { 
		u16 i=0;
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
		delay_init();	    	 //��ʱ������ʼ��	  
		uart_init(115200);	 	//���ڳ�ʼ��Ϊ9600
		LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
		EXTIX_Init(); 	
		AT24CXX_Init();			//IIC��ʼ�� 
		AD7746Init();

		CDC_WRREG(0x08,0x01);	//�رյ�ѹת��
		CDC_WRREG(0x09,0x1b);	//���ü���ԴEXCA��EXCB,��EXCB���ó�EXCA�ĵ���
		CDC_WRREG(0x0A,0x31);	//����ת��ģʽ��ת��ʱ������������
		
		CDC_WRREG(0x0B,0xff);	//CAPDAC����
		CDC_WRREG(0x0C,0xe2);	//CAPDAC���ã�0x0B - 0x0C = 0xff - 0xe2 -->0~100pF
		

	while(1)
	{
		CDC_WRREG(0x07,0x80);	//ѡ�����ת��ͨ����0x80:��1��2,0xc0:��1��2	    
	}
}
