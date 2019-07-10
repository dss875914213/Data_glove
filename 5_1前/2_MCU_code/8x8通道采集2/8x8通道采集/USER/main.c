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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口	 	
	//AT24CXX_Init();			//IIC初始化 
	IIC_Init();
	AD7746Init();
	//CD4051_Init();
	

	CDC_WRREG(0x08,0x01,IIC_NUM);	//关闭电压转换
	CDC_WRREG(0x09,0x1b,IIC_NUM);	//配置激励源EXCA和EXCB,将EXCB配置成EXCA的倒数
	CDC_WRREG(0x0A,0x09,IIC_NUM);	//连续转换模式，转换时间最长，精度最高
	
	CDC_WRREG(0x0B,0xff,IIC_NUM);	//CAPDAC配置
	CDC_WRREG(0x0C,0xe2,IIC_NUM);	//CAPDAC配置，0x0B - 0x0C = 0xff - 0xe2 -->0~100pF
	
	width = 4;

	while(1)
	{

		CDC_WRREG(0x07,0x80,IIC_NUM);	//选择电容转换通道，0x80:开1关2,0xc0:关1开2	 
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
			LED0=!LED0;//提示系统正在运行	
			i=0;
		}		   
	}
}
