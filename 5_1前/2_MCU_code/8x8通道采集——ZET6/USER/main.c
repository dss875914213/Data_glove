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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 //延时函数初始化	  
	//uart_init(115200);	 	//串口初始化为9600
	//LED_Init();		  		//初始化与LED连接的硬件接口	 	
	//AT24CXX_Init();			//IIC初始化 

	//AD7746Init();
	CD4051_Init();
	//IIC_Init();
	//RDY_Init();
//	for(chips=1;chips<4;chips++)
//  {
//		CDC_WRREG(0x08,0x01,chips);	//关闭电压转换
//		CDC_WRREG(0x09,0x1b,chips);	//配置激励源EXCA和EXCB,将EXCB配置成EXCA的倒数
//		CDC_WRREG(0x0A,0x09,chips);	//连续转换模式，转换时间最长，精度最高
//		
//		CDC_WRREG(0x0B,0xff,chips);	//CAPDAC配置
//		CDC_WRREG(0x0C,0xe2,chips);	//CAPDAC配置，0x0B - 0x0C = 0xff - 0xe2 -->0~100pF
//		//选择电容转换通道，0x80:开1关2,0xc0:关1开2	 
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
//			LED0=!LED0;//提示系统正在运行	
//			i=0;
//		}		   
	}
}

