#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK mini�SSTM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 �˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
	 GPIO_SetBits(GPIOA,GPIO_Pin_8);						 //PA.8 �����

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 �˿�����, �������
	 GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	 GPIO_ResetBits(GPIOD,GPIO_Pin_2); 						 //PD.2 ����� 
	
// CD4051����˿ڶ���		
//	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PC,PB�˿�ʱ��
//		
//	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_0|GPIO_Pin_2;				 //CD4051(0)A-->PC.2  B-->PC.0   C-->PC.13 �˿�����
//	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
//	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
//	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC
//	 GPIO_SetBits(GPIOC,GPIO_Pin_13);						 //PC.13 �����
//	 GPIO_SetBits(GPIOC,GPIO_Pin_0);						 //PC.0 �����
//	 GPIO_SetBits(GPIOC,GPIO_Pin_2);						 //PC.2 �����
//		 
//	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_10;				 //CD4051(1)B-->PC.10   C-->PC.3 �˿�����
//	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
//	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
//	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
//	 GPIO_SetBits(GPIOC,GPIO_Pin_10);						 //PC.10 �����
//	 GPIO_SetBits(GPIOC,GPIO_Pin_3);						 //PC.3 �����
//	 
//	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	    		 //CD4051(2)A-->PB.15 �˿�����, �������
//	 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
//	 GPIO_SetBits(GPIOB,GPIO_Pin_15); 						 //PB.15 ����� 	
}
 
