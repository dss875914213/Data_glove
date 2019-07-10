#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//IIC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/10 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

//C11,C12   	   		   
//IO��������
#define SDA_IN_1()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}//12/4+8=11
#define SDA_OUT_1() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}

//IO��������	 
#define IIC_SCL_1    PCout(12) //SCL
#define IIC_SDA_1    PCout(11) //SDA	 
#define READ_SDA_1   PCin(11)  //����SDA 


//C4,C5
//IO��������
#define SDA_IN_2()  {GPIOC->CRL&=0XFFF0FFFF;GPIOC->CRL|=8<<16;}
#define SDA_OUT_2() {GPIOC->CRL&=0XFFF0FFFF;GPIOC->CRL|=3<<16;}

//IO��������	 
#define IIC_SCL_2    PCout(5) //SCL
#define IIC_SDA_2    PCout(4) //SDA	 
#define READ_SDA_2   PCin(4)  //����SDA 

//A14,A15
//IO��������
#define SDA_IN_3()  {GPIOA->CRH&=0XF0FFFFFF;GPIOA->CRH|=8<<24;}
#define SDA_OUT_3() {GPIOA->CRH&=0XF0FFFFFF;GPIOA->CRH|=3<<24;}

//IO��������	 
#define IIC_SCL_3    PAout(15) //SCL
#define IIC_SDA_3    PAout(14) //SDA	 
#define READ_SDA_3   PAin(14)  //����SDA 

//A12,A13
//IO��������
#define SDA_IN_4()  {GPIOA->CRH&=0XFFF0FFFF;GPIOA->CRH|=8<<16;}
#define SDA_OUT_4() {GPIOA->CRH&=0XFFF0FFFF;GPIOA->CRH|=3<<16;}

//IO��������	 
#define IIC_SCL_4    PAout(13) //SCL
#define IIC_SDA_4    PAout(12) //SDA	 
#define READ_SDA_4   PAin(12)  //����SDA 




//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(u8 num_IIC);				//����IIC��ʼ�ź�
void IIC_Stop(u8 num_IIC);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd,u8 num_IIC);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack,u8 num_IIC);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(u8 num_IIC); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(u8 num_IIC);					//IIC����ACK�ź�
void IIC_NAck(u8 num_IIC);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  




void Read_Config(u8 num_IIC);





#endif
















