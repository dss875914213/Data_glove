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
#include "CD4051.h"
#include "rdy.h"

u8 temp = 0,tempdata = 0;
u8 channeli = 0,channelj = 0;

u8 width = 0;
float cap = 0.0;
   	
//#define IIC_NUM 3
#define delay_time 50
int matrix[4][4]=
	{{1,2,3,4},
	{9,10,11,12},
	{17,18,19,20},
	{25,26,27,28}};
int matrix_chip[4]={0,4,32,36};
int main(void)
 { 
	int IIC_NUM=0;
	u16 i=0,chips=0;
//	char flag=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	delay_init();	    	 //��ʱ������ʼ��	  
	//uart_init(115200);	 	//���ڳ�ʼ��Ϊ9600
	//LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�	 	
	//AT24CXX_Init();			//IIC��ʼ�� 

	//AD7746Init();
	CD4051_Init();
	//IIC_Init();
	//RDY_Init();
//	for(chips=1;chips<4;chips++)
//  {
//		CDC_WRREG(0x08,0x01,chips);	//�رյ�ѹת��
//		CDC_WRREG(0x09,0x1b,chips);	//���ü���ԴEXCA��EXCB,��EXCB���ó�EXCA�ĵ���
//		CDC_WRREG(0x0A,0x09,chips);	//����ת��ģʽ��ת��ʱ������������
//		
//		CDC_WRREG(0x0B,0xff,chips);	//CAPDAC����
//		CDC_WRREG(0x0C,0xe2,chips);	//CAPDAC���ã�0x0B - 0x0C = 0xff - 0xe2 -->0~100pF
//		//ѡ�����ת��ͨ����0x80:��1��2,0xc0:��1��2	 
//		CDC_WRREG(0x07,0x80,chips);	
//  }
	
	
	width = 4;
//	Switch1_Up_INH = Switch_Off;
//	Switch2_Up_INH = Switch_Off;
//	Switch3_Up_INH = Switch_On;
//	Switch4_Up_INH = Switch_Off;
//	Switch1_Down_INH = Switch_Off;
//	Switch2_Down_INH = Switch_Off;
//	Switch3_Down_INH = Switch_On;
//	Switch4_Down_INH = Switch_Off;
	IIC_NUM=4;
	while(1)
	{	
//		if(IIC_NUM==1)
//		{
//			Switch1_Up_INH = Switch_On;
//			Switch2_Up_INH = Switch_Off;
//			Switch3_Up_INH = Switch_Off;
//			Switch4_Up_INH = Switch_Off;
//			Switch1_Down_INH = Switch_On;
//			Switch2_Down_INH = Switch_Off;
//			Switch3_Down_INH = Switch_Off;
//			Switch4_Down_INH = Switch_Off;
//		}
//		else if(IIC_NUM==2)
//		{
//			Switch1_Up_INH = Switch_Off;
//			Switch2_Up_INH = Switch_On;
//			Switch3_Up_INH = Switch_Off;
//			Switch4_Up_INH = Switch_Off;
//			Switch1_Down_INH = Switch_Off;
//			Switch2_Down_INH = Switch_On;
//			Switch3_Down_INH = Switch_Off;
//			Switch4_Down_INH = Switch_Off;
//		}
//		else if(IIC_NUM==3)
//		{
//			Switch1_Up_INH = Switch_Off;
//			Switch2_Up_INH = Switch_Off;
//			Switch3_Up_INH = Switch_On;
//			Switch4_Up_INH = Switch_Off;
//			Switch1_Down_INH = Switch_Off;
//			Switch2_Down_INH = Switch_Off;
//			Switch3_Down_INH = Switch_On;
//			Switch4_Down_INH = Switch_Off;
//		}
//		else if(IIC_NUM==4)
//		{
//			Switch1_Up_INH = Switch_Off;
//			Switch2_Up_INH = Switch_Off;
//			Switch3_Up_INH = Switch_Off;
//			Switch4_Up_INH = Switch_On;
//			Switch1_Down_INH = Switch_Off;
//			Switch2_Down_INH = Switch_Off;
//			Switch3_Down_INH = Switch_Off;
//			Switch4_Down_INH = Switch_On;
//		}
//		
//			temp = CDC_RDREG(0x00,IIC_NUM);
//		printf("%d\r\n",temp);
//		delay_ms(50);
////		for(channeli=0; channeli<width; channeli++)
////		{
////			for(channelj=0; channelj<width; channelj++)
////			{
////				
////				CD4051_Switch_Up(channeli,IIC_NUM);
////				CD4051_Switch_Down(channelj,IIC_NUM);
////				//delay_ms(1);
////				while(1)
////				{
////					temp = CDC_RDREG(0x00,IIC_NUM);
////					if(temp == 0x02)
////						break;
////				}
////				//if(temp == 0x02)
////				{
//////					if(channeli==0 && channelj==0)
//////					{
//////						delay_ms(40);
//////					}
////					delay_ms(50);//50
////					//Switch4_Down_INH=0;
////					cap = Read_7746data(IIC_NUM);
////					printf("%d	%f\r\n",matrix[channeli][channelj]+matrix_chip[IIC_NUM-1],cap);
////					//Switch4_Down_INH=1;
////					//delay_ms(2);
////				}
////			}
////		}
//		//delay_ms(500);
//		if(temp == 0x02)
//		{
//			IIC_NUM+=1;
//		}
//		if(IIC_NUM>4)
//		{
//			IIC_NUM=1;
//		}
//			
//		i++;
//		if(i==10)
//		{
//			LED0=!LED0;//��ʾϵͳ��������	
//			i=0;
//		}		   
	}
}

