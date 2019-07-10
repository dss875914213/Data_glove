#include <stdio.h>
#include "AD7746.h"
#include "myiic.h"

//Cap result
unsigned char CapResult_H,CapResult_M,CapResult_L;
char IIC_Flag;
unsigned long SUMPID;
float Cgod,cappos = 0;

/**************************************************************************************
o¡¥¨ºy??3?¡êoAD7746?¡ä??o¡¥¨ºyCDC_Reset
1|    ?¨¹¡êo?¡ä??AD7746
2?    ¨ºy¡êo?T
¡¤¦Ì???¦Ì  ¡êo?T
*****************************************************************************************/
void CDC_Reset(u8 num_IIC)	
{
	unsigned char i;
	IIC_Start(num_IIC);
	IIC_Send_Byte(SLAVEADD,num_IIC);
	if(!(IIC_Flag&(1<<NOACK)))
		IIC_Send_Byte(CDC_RESET_ADDR,num_IIC);
	else
		IIC_Flag |= 1<<ERR;
	IIC_Stop(num_IIC);
	
	for(i=0;i<254;i++);	//wait for CDC reset
}

/**************************************************************************************
??    3?¡êoIICD¡ä??¡ä??¡Â¨º¡ÀD¨°o¡¥¨ºy
1|    ?¨¹¡êo?¨°???¡§??¡ä??¡Â¡¤¡é?¨ª¡Á??¨²o¡¥¨ºy
2?    ¨ºy¡êo¡¤¡é?¨ª¦Ì?¦Ì??¡¤¨®?¨ºy?Y
¡¤¦Ì???¦Ì  ¡êo?T
*****************************************************************************************/
void CDC_WRREG(unsigned char addr, unsigned char reg,u8 num_IIC)	
{
	IIC_Start(num_IIC);
	IIC_Send_Byte(SLAVEADD,num_IIC);
	if(!(IIC_Flag&(1<<NOACK)))
		IIC_Send_Byte(addr,num_IIC);
	if(!(IIC_Flag&(1<<NOACK)))
		IIC_Send_Byte(reg,num_IIC);
	IIC_Stop(num_IIC);
	if(IIC_Flag&(1<<NOACK))
		IIC_Flag |= 1<<ERR;
}

/**************************************************************************************
??    3?¡êoIIC?¨¢??¡ä??¡Â¨º¡ÀD¨°o¡¥¨ºy
1|    ?¨¹¡êo?¨¢3????¡§??¡ä??¡Â¦Ì?¨ºy?Y
2?    ¨ºy¡êo?¨¢¨¨?¦Ì???¡ä??¡Â¦Ì??¡¤
¡¤¦Ì???¦Ì  ¡êo¡¤¦Ì???¨¢¨¨?¦Ì??¦Ì
*****************************************************************************************/
unsigned char CDC_RDREG(unsigned char addr,u8 num_IIC)
{
	unsigned char rr;
	IIC_Start(num_IIC);
	IIC_Send_Byte(SLAVEADD,num_IIC);
	if(!(IIC_Flag&(1<<NOACK)))
		IIC_Send_Byte(addr,num_IIC);
	if(!(IIC_Flag&(1<<NOACK)))
	{
		IIC_Start(num_IIC);				//re-start
		IIC_Send_Byte(SLAVEADD+1,num_IIC);	//read function
	}
	if(!(IIC_Flag&(1<<NOACK)))
		rr = IIC_Read_Byte(1,num_IIC);		//read 1 byte, no ack
	IIC_Stop(num_IIC);
	if(IIC_Flag&(1<<NOACK))
		IIC_Flag |= 1<<ERR;
	return rr;
}



/**************************************************************************************
??    3?¡êo?¨¢¨¨?AD7746¨ºy?¦Ì??¡ä??¡Âo¡¥¨ºy
1|    ?¨¹¡êo?¨¢¨¨?AD7746¦Ì?¨ºy?Y??¡ä??¡Â?¦Ì¡¤?¨¨?CapResult_HCapResult_M¡ê?CapResult_L
2?    ¨ºy¡êo?T
¡¤¦Ì???¦Ì  ¡êo?T
*****************************************************************************************/
void CDC_RDCAP(u8 num_IIC)
{
	IIC_Start(num_IIC);
	IIC_Send_Byte(SLAVEADD,num_IIC);
	if(!(IIC_Flag&(1<<NOACK)))
		IIC_Send_Byte(CDC_CAPDATA_ADDR,num_IIC);
	if(!(IIC_Flag&(1<<NOACK)))
	{
		IIC_Start(num_IIC);				//re-start
		IIC_Send_Byte(SLAVEADD+1,num_IIC);	//read function
	}
	if(!(IIC_Flag&(1<<NOACK)))
		CapResult_H = IIC_Read_Byte(0,num_IIC);	//read cap data reg
	if(!(IIC_Flag&(1<<NOACK)))
		CapResult_M = IIC_Read_Byte(0,num_IIC);
	if(!(IIC_Flag&(1<<NOACK)))
		CapResult_L = IIC_Read_Byte(1,num_IIC);		
	IIC_Stop(num_IIC);
	if(IIC_Flag&(1<<NOACK))
		IIC_Flag |= 1<<ERR;
}


/**************************************************************************************
??    3?¡êo3?¨º??¡¥o¡¥¨ºy
1|    ?¨¹¡êo3?¨º??¡¥AD7746¦Ì?1|?¨¹
2?    ¨ºy¡êo?T
¡¤¦Ì???¦Ì  ¡êo?T
*****************************************************************************************/
void AD7746Init(void)
{
	u8 switchs;
	//Rdy¨°y??????:PC1
//	GPIO_InitTypeDef GPIO_InitStructure;
	
//	__HAL_RCC_GPIOC_CLK_ENABLE();
////	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//1?¡À?jtag¡ê?¨º1?¨¹SWD¡ê??¨¦¨°?¨®?SWD?¡ê¨º?¦Ì¡Â¨º?
//	
//	GPIO_InitStructure.Pin  = GPIO_PIN_1;//PC1
//	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
//	GPIO_InitStructure.Pull = GPIO_PULLUP; //¨¦¨¨??3¨¦¨¦?¨¤-¨º?¨¨?
// 	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);//3?¨º??¡¥GPIOC1
		
	for(switchs=1;switchs<=4;switchs++)
	{
		CDC_Reset(switchs);
	}


	if(IIC_Flag&(1<<ERR))
	{
		IIC_Flag = 0;
//		send_achar('#');   //if there's any error 
	}
	cappos=(float)17*CAPDAC/0x7F;

	
}

/**************************************************************************************
??    3?¡êoAD7746¡Áa?¡¥¦Ì?¨¨Y?¦Ìo¡¥¨ºy
1|    ?¨¹¡êo¡ã?AD7746¨ºy?Y??¡ä??¡Â?¦Ì¡Áa?¡¥?a¦Ì?¨¨Y?¦Ì
2?    ¨ºy¡êo?T
¡¤¦Ì???¦Ì  ¡êo?T
*****************************************************************************************/
float Read_7746data(u8 num_IIC)
{
	long DATA,H,M,L;
	float ma;
	CDC_RDCAP(num_IIC);
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
??    3?¡êoCD4051_Switch
1|    ?¨¹¡êo??¨ª¡§CD4051¨ª¡§¦Ì¨¤¡ê?¨¢????¡é????4¨ª¡§¦Ì¨¤
2?    ¨ºy¡êo?T
¡¤¦Ì???¦Ì  ¡êo?T
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
}

