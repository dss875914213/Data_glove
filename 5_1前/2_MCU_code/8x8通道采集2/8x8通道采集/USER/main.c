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
//#include "CD4051.h"

u8 temp = 0,tempdata = 0;
u8 channeli = 0,channelj = 0;

u8 width = 0;
float cap = 0.0;
   	
#define IIC_NUM 2
 int main(void)
 { 
	u16 i=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�	 	
	//AT24CXX_Init();			//IIC��ʼ�� 
	IIC_Init();
	AD7746Init();
	//CD4051_Init();
	

	CDC_WRREG(0x08,0x01,IIC_NUM);	//�رյ�ѹת��
	CDC_WRREG(0x09,0x1b,IIC_NUM);	//���ü���ԴEXCA��EXCB,��EXCB���ó�EXCA�ĵ���
	CDC_WRREG(0x0A,0x09,IIC_NUM);	//����ת��ģʽ��ת��ʱ������������
	
	CDC_WRREG(0x0B,0xff,IIC_NUM);	//CAPDAC����
	CDC_WRREG(0x0C,0xe2,IIC_NUM);	//CAPDAC���ã�0x0B - 0x0C = 0xff - 0xe2 -->0~100pF
	
	width = 4;

	while(1)
	{

		CDC_WRREG(0x07,0x80,IIC_NUM);	//ѡ�����ת��ͨ����0x80:��1��2,0xc0:��1��2	 
		temp = CDC_RDREG(0x00,IIC_NUM);	
		Read_Config(IIC_NUM);
		printf("%d\r\n",temp);
		for(channeli=0; channeli<width; channeli++)
		{
			for(channelj=0; channelj<width; channelj++)
			{
				CD4051_Switch(0, channeli);
				CD4051_Switch(1, channelj);
				if(temp == 0x02)
				{
					delay_ms(50);
					cap = Read_7746data(IIC_NUM);
					printf("%d	%lf\r\n",width*channeli+channelj+1,cap);
				}
			}
		}
		i++;
		if(i==10)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			i=0;
		}		   
	}
}
