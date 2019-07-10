#include <stdio.h>
#include "AD7746.h"
#include "myiic.h"

//Cap result
unsigned char CapResult_H,CapResult_M,CapResult_L;
char IIC_Flag;
unsigned long SUMPID;
float Cgod,cappos = 0;

/**************************************************************************************
函数名称：AD7746复位函数CDC_Reset
功    能：复位AD7746
参    数：无
返回值  ：无
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
名    称：IIC写寄存器时序函数
功    能：向指定寄存器发送字节函数
参    数：发送的地址与数据
返回值  ：无
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
名    称：IIC读寄存器时序函数
功    能：读出指定寄存器的数据
参    数：读取的寄存器地址
返回值  ：返回读取的值
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
名    称：读取AD7746数值寄存器函数
功    能：读取AD7746的数据寄存器值放入CapResult_HCapResult_M，CapResult_L
参    数：无
返回值  ：无
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
名    称：初始化函数
功    能：初始化AD7746的功能
参    数：无
返回值  ：无
*****************************************************************************************/
void AD7746Init(void)
{
	//Rdy引脚配置:PC1
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTC时钟

//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//PC1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC1
		
	CDC_Reset();
	//REG SETUP refs to AD7746EVB's software
//	CDC_WRREG(0x0A,0x31);	//CON REG,CAPF=111,MD=001,9.1Hz
//	CDC_WRREG(0x0B,CAPDAC+0x80);	//CAP DAC A
//	CDC_WRREG(0x09,0x0B);	//EXC REG,EXCA,EXCLVL=11
//	CDC_WRREG(0x07,0x80);	//CAP SET-UP,start

//	CDC_WRREG(0x07,0x80);	//选择电容转换通道，0x80:开1关2,0xc0:关1开2
//	CDC_WRREG(0x08,0x01);	//关闭电压转换
//	CDC_WRREG(0x09,0x1b);	//配置激励源EXCA和EXCB,将EXCB配置成EXCA的倒数
//	CDC_WRREG(0x0A,0x39);	//连续转换模式，转换时间最长，精度最高
//	CDC_WRREG(0x0B,0xff);	//CAPDAC配置
//	CDC_WRREG(0x0C,0xe2);	//CAPDAC配置，0x0B - 0x0C = 0xff - 0xe2 -->0~100pF	

//	CDC_WRREG(0x07,0x80);	//选择电容转换通道，0x80:开1关2,0xc0:关1开2
//	CDC_WRREG(0x08,0x01);	//关闭电压转换
//	CDC_WRREG(0x09,0x0b);	//配置激励源EXCA和EXCB,将EXCB配置成EXCA的倒数
//	CDC_WRREG(0x0A,0x22);	//连续转换模式，转换时间最长，精度最高
//	CDC_WRREG(0x0B,0x00);	//CAPDAC配置
//	CDC_WRREG(0x0C,0x00);	//CAPDAC配置，0x0B - 0x0C = 0xff - 0xe2 -->0~100pF	

	if(IIC_Flag&(1<<ERR))
	{
		IIC_Flag = 0;
//		send_achar('#');   //if there's any error 
	}
	cappos=(float)17*CAPDAC/0x7F;

	
}

/**************************************************************************************
名    称：AD7746转化电容值函数
功    能：把AD7746数据寄存器值转化为电容值
参    数：无
返回值  ：无
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
名    称：CD4051_Switch
功    能：选通CD4051通道，两片、每片4通道
参    数：无
返回值  ：无
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

