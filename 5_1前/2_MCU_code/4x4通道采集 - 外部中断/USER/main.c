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
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
		delay_init();	    	 //延时函数初始化	  
		uart_init(115200);	 	//串口初始化为9600
		LED_Init();		  		//初始化与LED连接的硬件接口
		EXTIX_Init(); 	
		AT24CXX_Init();			//IIC初始化 
		AD7746Init();

		CDC_WRREG(0x08,0x01);	//关闭电压转换
		CDC_WRREG(0x09,0x1b);	//配置激励源EXCA和EXCB,将EXCB配置成EXCA的倒数
		CDC_WRREG(0x0A,0x31);	//连续转换模式，转换时间最长，精度最高
		
		CDC_WRREG(0x0B,0xff);	//CAPDAC配置
		CDC_WRREG(0x0C,0xe2);	//CAPDAC配置，0x0B - 0x0C = 0xff - 0xe2 -->0~100pF
		

	while(1)
	{
		CDC_WRREG(0x07,0x80);	//选择电容转换通道，0x80:开1关2,0xc0:关1开2	    
	}
}
