#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);	 //使能PA,PD端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
	 GPIO_SetBits(GPIOA,GPIO_Pin_8);						 //PA.8 输出高

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 端口配置, 推挽输出
	 GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	 GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 //PD.2 输出高 
	
// CD4051输出端口定义		
//	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB, ENABLE);	 //使能PC,PB端口时钟
//		
//	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_0|GPIO_Pin_2;				 //CD4051(0)A-->PC.2  B-->PC.0   C-->PC.13 端口配置
//	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
//	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
//	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC
//	 GPIO_SetBits(GPIOC,GPIO_Pin_13);						 //PC.13 输出高
//	 GPIO_SetBits(GPIOC,GPIO_Pin_0);						 //PC.0 输出高
//	 GPIO_SetBits(GPIOC,GPIO_Pin_2);						 //PC.2 输出高
//		 
//	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_10;				 //CD4051(1)B-->PC.10   C-->PC.3 端口配置
//	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
//	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
//	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
//	 GPIO_SetBits(GPIOC,GPIO_Pin_10);						 //PC.10 输出高
//	 GPIO_SetBits(GPIOC,GPIO_Pin_3);						 //PC.3 输出高
//	 
//	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	    		 //CD4051(2)A-->PB.15 端口配置, 推挽输出
//	 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
//	 GPIO_SetBits(GPIOB,GPIO_Pin_15); 						 //PB.15 输出高 	
}
 
