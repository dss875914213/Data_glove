#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//IIC 驱动函数	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/6/10 
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

//C11,C12   	   		   
//IO方向设置
#define SDA_IN_1()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}//12/4+8=11
#define SDA_OUT_1() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}

//IO操作函数	 
#define IIC_SCL_1    PCout(12) //SCL
#define IIC_SDA_1    PCout(11) //SDA	 
#define READ_SDA_1   PCin(11)  //输入SDA 


//C4,C5
//IO方向设置
#define SDA_IN_2()  {GPIOC->CRL&=0XFFF0FFFF;GPIOC->CRL|=8<<16;}
#define SDA_OUT_2() {GPIOC->CRL&=0XFFF0FFFF;GPIOC->CRL|=3<<16;}

//IO操作函数	 
#define IIC_SCL_2    PCout(5) //SCL
#define IIC_SDA_2    PCout(4) //SDA	 
#define READ_SDA_2   PCin(4)  //输入SDA 

//A14,A15
//IO方向设置
#define SDA_IN_3()  {GPIOA->CRH&=0XF0FFFFFF;GPIOA->CRH|=8<<24;}
#define SDA_OUT_3() {GPIOA->CRH&=0XF0FFFFFF;GPIOA->CRH|=3<<24;}

//IO操作函数	 
#define IIC_SCL_3    PAout(15) //SCL
#define IIC_SDA_3    PAout(14) //SDA	 
#define READ_SDA_3   PAin(14)  //输入SDA 

//A12,A13
//IO方向设置
#define SDA_IN_4()  {GPIOA->CRH&=0XFFF0FFFF;GPIOA->CRH|=8<<16;}
#define SDA_OUT_4() {GPIOA->CRH&=0XFFF0FFFF;GPIOA->CRH|=3<<16;}

//IO操作函数	 
#define IIC_SCL_4    PAout(13) //SCL
#define IIC_SDA_4    PAout(12) //SDA	 
#define READ_SDA_4   PAin(12)  //输入SDA 




//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(u8 num_IIC);				//发送IIC开始信号
void IIC_Stop(u8 num_IIC);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd,u8 num_IIC);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack,u8 num_IIC);//IIC读取一个字节
u8 IIC_Wait_Ack(u8 num_IIC); 				//IIC等待ACK信号
void IIC_Ack(u8 num_IIC);					//IIC发送ACK信号
void IIC_NAck(u8 num_IIC);				//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  




void Read_Config(u8 num_IIC);





#endif
















