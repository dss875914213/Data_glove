#include <stdio.h>
#include "AD7746.h"
#include "myiic.h"

//Cap result
unsigned char CapResult_H,CapResult_M,CapResult_L;
char IIC_Flag;
unsigned long SUMPID;
float Cgod,cappos = 0;

/**************************************************************************************
�������ƣ�AD7746��λ����CDC_Reset
��    �ܣ���λAD7746
��    ������
����ֵ  ����
*****************************************************************************************/
void CDC_Reset(void)	
{
	unsigned char i;
	IIC_Start();
	IIC_Send_Byte(SLAVEADD);
	if(!(IIC_Flag&(1<<NOACK)))
		IIC_Send_Byte(CDC_RESET_ADDR);
	else
		IIC_Flag |= 1<<ERR;
	IIC_Stop();
	
	for(i=0;i<254;i++);	//wait for CDC reset
}

/**************************************************************************************
��    �ƣ�IICд�Ĵ���ʱ����
��    �ܣ���ָ���Ĵ��������ֽں���
��    �������͵ĵ�ַ������
����ֵ  ����
*****************************************************************************************/
void CDC_WRREG(unsigned char addr, unsigned char reg)	
{
	IIC_Start();
	IIC_Send_Byte(SLAVEADD);
	if(!(IIC_Flag&(1<<NOACK)))
		IIC_Send_Byte(addr);
	if(!(IIC_Flag&(1<<NOACK)))
		IIC_Send_Byte(reg);
	IIC_Stop();
	if(IIC_Flag&(1<<NOACK))
		IIC_Flag |= 1<<ERR;
}

/**************************************************************************************
��    �ƣ�IIC���Ĵ���ʱ����
��    �ܣ�����ָ���Ĵ���������
��    ������ȡ�ļĴ�����ַ
����ֵ  �����ض�ȡ��ֵ
*****************************************************************************************/
unsigned char CDC_RDREG(unsigned char addr)
{
	unsigned char rr;
	IIC_Start();
	IIC_Send_Byte(SLAVEADD);
	if(!(IIC_Flag&(1<<NOACK)))
		IIC_Send_Byte(addr);
	if(!(IIC_Flag&(1<<NOACK)))
	{
		IIC_Start();				//re-start
		IIC_Send_Byte(SLAVEADD+1);	//read function
	}
	if(!(IIC_Flag&(1<<NOACK)))
		rr = IIC_Read_Byte(1);		//read 1 byte, no ack
	IIC_Stop();
	if(IIC_Flag&(1<<NOACK))
		IIC_Flag |= 1<<ERR;
	return rr;
}

/**************************************************************************************
��    �ƣ���ȡAD7746��ֵ�Ĵ�������
��    �ܣ���ȡAD7746�����ݼĴ���ֵ����CapResult_HCapResult_M��CapResult_L
��    ������
����ֵ  ����
*****************************************************************************************/
void CDC_RDCAP(void)
{
	IIC_Start();
	IIC_Send_Byte(SLAVEADD);
	if(!(IIC_Flag&(1<<NOACK)))
		IIC_Send_Byte(CDC_CAPDATA_ADDR);
	if(!(IIC_Flag&(1<<NOACK)))
	{
		IIC_Start();				//re-start
		IIC_Send_Byte(SLAVEADD+1);	//read function
	}
	if(!(IIC_Flag&(1<<NOACK)))
		CapResult_H = IIC_Read_Byte(0);	//read cap data reg
	if(!(IIC_Flag&(1<<NOACK)))
		CapResult_M = IIC_Read_Byte(0);
	if(!(IIC_Flag&(1<<NOACK)))
		CapResult_L = IIC_Read_Byte(1);		
	IIC_Stop();
	if(IIC_Flag&(1<<NOACK))
		IIC_Flag |= 1<<ERR;
}


/**************************************************************************************
��    �ƣ���ʼ������
��    �ܣ���ʼ��AD7746�Ĺ���
��    ������
����ֵ  ����
*****************************************************************************************/
void AD7746Init(void)
{
	//Rdy��������:PC1
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTCʱ��

//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//PC1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC1
		
	CDC_Reset();
	//REG SETUP refs to AD7746EVB's software
//	CDC_WRREG(0x0A,0x31);	//CON REG,CAPF=111,MD=001,9.1Hz
//	CDC_WRREG(0x0B,CAPDAC+0x80);	//CAP DAC A
//	CDC_WRREG(0x09,0x0B);	//EXC REG,EXCA,EXCLVL=11
//	CDC_WRREG(0x07,0x80);	//CAP SET-UP,start

//	CDC_WRREG(0x07,0x80);	//ѡ�����ת��ͨ����0x80:��1��2,0xc0:��1��2
//	CDC_WRREG(0x08,0x01);	//�رյ�ѹת��
//	CDC_WRREG(0x09,0x1b);	//���ü���ԴEXCA��EXCB,��EXCB���ó�EXCA�ĵ���
//	CDC_WRREG(0x0A,0x39);	//����ת��ģʽ��ת��ʱ������������
//	CDC_WRREG(0x0B,0xff);	//CAPDAC����
//	CDC_WRREG(0x0C,0xe2);	//CAPDAC���ã�0x0B - 0x0C = 0xff - 0xe2 -->0~100pF	

//	CDC_WRREG(0x07,0x80);	//ѡ�����ת��ͨ����0x80:��1��2,0xc0:��1��2
//	CDC_WRREG(0x08,0x01);	//�رյ�ѹת��
//	CDC_WRREG(0x09,0x0b);	//���ü���ԴEXCA��EXCB,��EXCB���ó�EXCA�ĵ���
//	CDC_WRREG(0x0A,0x22);	//����ת��ģʽ��ת��ʱ������������
//	CDC_WRREG(0x0B,0x00);	//CAPDAC����
//	CDC_WRREG(0x0C,0x00);	//CAPDAC���ã�0x0B - 0x0C = 0xff - 0xe2 -->0~100pF	

	if(IIC_Flag&(1<<ERR))
	{
		IIC_Flag = 0;
//		send_achar('#');   //if there's any error 
	}
	cappos=(float)17*CAPDAC/0x7F;

	
}

/**************************************************************************************
��    �ƣ�AD7746ת������ֵ����
��    �ܣ���AD7746���ݼĴ���ֵת��Ϊ����ֵ
��    ������
����ֵ  ����
*****************************************************************************************/
float Read_7746data(void)
{
	long DATA,H,M,L;
	float ma;
	CDC_RDCAP();
	H=CapResult_H;
	M=CapResult_M;
	L=CapResult_L;
	DATA=(H<<16)|(M<<8)|L;
	SUMPID=DATA;
//	ma=(float)DATA*8.192/0xFFFFFF+cappos-4.096;
	ma = DATA*5.91278e-6;
	return ma;
}

/**************************************************************************************
��    �ƣ�CD4051_Switch
��    �ܣ�ѡͨCD4051ͨ������Ƭ��ÿƬ4ͨ��
��    ������
����ֵ  ����
*****************************************************************************************/
void CD4051_Switch(u8 chip, u8 channel)
{
	if(chip == 0)
	{
		if(channel == 0)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_3);
			GPIO_ResetBits(GPIOC,GPIO_Pin_10);
			GPIO_ResetBits(GPIOB,GPIO_Pin_15);			
		}
		else if(channel == 1)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_3);
			GPIO_ResetBits(GPIOC,GPIO_Pin_10);
			GPIO_SetBits(GPIOB,GPIO_Pin_15);
		}
		else if(channel == 2)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_3);
			GPIO_SetBits(GPIOC,GPIO_Pin_10);
			GPIO_ResetBits(GPIOB,GPIO_Pin_15);
		}
		else if(channel == 3)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_3);
			GPIO_SetBits(GPIOC,GPIO_Pin_10);
			GPIO_SetBits(GPIOB,GPIO_Pin_15);
		}
	}
	else
	{
		if(channel == 0)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			GPIO_ResetBits(GPIOC,GPIO_Pin_0);
			GPIO_ResetBits(GPIOC,GPIO_Pin_2);
		}
		else if(channel == 1)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			GPIO_ResetBits(GPIOC,GPIO_Pin_0);
			GPIO_SetBits(GPIOC,GPIO_Pin_2);	
		}
		else if(channel == 2)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			GPIO_SetBits(GPIOC,GPIO_Pin_0);
			GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
		}
		else if(channel == 3)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			GPIO_SetBits(GPIOC,GPIO_Pin_0);
			GPIO_SetBits(GPIOC,GPIO_Pin_2);
		}
	}
	
//	switch(chip)
//	{
//		case 0:
//		{
//			switch(channel)
//			{
//				case 0:
//				{
//					GPIO_ResetBits(GPIOC,GPIO_Pin_3);
//					GPIO_ResetBits(GPIOC,GPIO_Pin_10);
//					GPIO_ResetBits(GPIOB,GPIO_Pin_15);
//				}
//				case 1:
//				{
//					GPIO_ResetBits(GPIOC,GPIO_Pin_3);
//					GPIO_ResetBits(GPIOC,GPIO_Pin_10);
//					GPIO_SetBits(GPIOB,GPIO_Pin_15);					
//				}
//				case 2:
//				{
//					GPIO_ResetBits(GPIOC,GPIO_Pin_3);
//					GPIO_SetBits(GPIOC,GPIO_Pin_10);
//					GPIO_ResetBits(GPIOB,GPIO_Pin_15);					
//				}
//				case 3:
//				{
//					GPIO_ResetBits(GPIOC,GPIO_Pin_3);
//					GPIO_SetBits(GPIOC,GPIO_Pin_10);
//					GPIO_SetBits(GPIOB,GPIO_Pin_15);					
//				}		
//			}				
//		}
//		case 1:
//		{
//			switch(channel)
//			{
//				case 0:
//				{
//					GPIO_ResetBits(GPIOC,GPIO_Pin_2);
//					GPIO_ResetBits(GPIOC,GPIO_Pin_0);
//					GPIO_ResetBits(GPIOC,GPIO_Pin_13);
//				}
//				case 1:
//				{
//					GPIO_ResetBits(GPIOC,GPIO_Pin_2);
//					GPIO_ResetBits(GPIOC,GPIO_Pin_0);
//					GPIO_SetBits(GPIOC,GPIO_Pin_13);					
//				}
//				case 2:
//				{
//					GPIO_ResetBits(GPIOC,GPIO_Pin_2);
//					GPIO_SetBits(GPIOC,GPIO_Pin_0);
//					GPIO_ResetBits(GPIOC,GPIO_Pin_13);					
//				}
//				case 3:
//				{
//					GPIO_ResetBits(GPIOC,GPIO_Pin_2);
//					GPIO_SetBits(GPIOC,GPIO_Pin_0);
//					GPIO_SetBits(GPIOC,GPIO_Pin_13);					
//				}
//			}
//					
//		}			
//	}
}

