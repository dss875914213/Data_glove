/*
Switch1_Up_A:			PD6   d
Switch1_Up_B:			PG12   g
Switch1_Up_C:			PD11  d
Switch1_Up_INH: 	PD12  d
Switch1_Down_A:		PD4   d
Switch1_Down_B:		PH12
Switch1_Down_C:		PD5   d
Switch1_Down_INH:	PA8  a

Switch2_Up_A:			PC9  c
Switch2_Up_B:			PC7  c
Switch2_Up_C:			PB15 b
Switch2_Up_INH: 	PB13 b
Switch2_Down_A:		PC8  c
Switch2_Down_B:		PC6  c
Switch2_Down_C:		PB14 b
Switch2_Down_INH:	PH8

Switch3_Up_A:			PC10 c
Switch3_Up_B:			PC12 c
Switch3_Up_C:			PD3   d
Switch3_Up_INH: 	PG10   g
Switch3_Down_A:		PC11  c
Switch3_Down_B:		PD2   d
Switch3_Down_C:		PD7   d
Switch3_Down_INH:	PA14  a

Switch4_Up_A:			PA13  a
Switch4_Up_B:			PC13  c
Switch4_Up_C:			PB8 b
Switch4_Up_INH: 	PB6 b
Switch4_Down_A:		PA15  a
Switch4_Down_B:		PB9 b 
Switch4_Down_C:		PB7 b
Switch4_Down_INH:	PB5 b

*/
#include "CD4051.h"

void CD4051_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTC时钟

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA15
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC5
 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0
}

void CD4051_Switch_Up(u8 channel,u8 switchs)
{
	GPIO_TypeDef* GPIO1;
	GPIO_TypeDef* GPIO2;
	GPIO_TypeDef* GPIO3;
	uint16_t GPIO_Pin1,GPIO_Pin2,GPIO_Pin3;
	
	if(switchs==1)
	{
		GPIO1 = GPIOE;
		GPIO2 = GPIOE;
		GPIO3 = GPIOE;
		GPIO_Pin1 = GPIO_Pin_1;
		GPIO_Pin2 = GPIO_Pin_3;
		GPIO_Pin3 = GPIO_Pin_5;
	}
	else if(switchs==2)
	{
		GPIO1 = GPIOF;
		GPIO2 = GPIOF;
		GPIO3 = GPIOF;
		GPIO_Pin1 = GPIO_Pin_1;
		GPIO_Pin2 = GPIO_Pin_3;
		GPIO_Pin3 = GPIO_Pin_5;
	}
	else if(switchs==3)
	{
		GPIO1 = GPIOF;
		GPIO2 = GPIOC;
		GPIO3 = GPIOC;
		GPIO_Pin1 = GPIO_Pin_9;
		GPIO_Pin2 = GPIO_Pin_0;
		GPIO_Pin3 = GPIO_Pin_2;
	}
	else if(switchs==4)
	{
		GPIO1 = GPIOA;
		GPIO2 = GPIOA;
		GPIO3 = GPIOC;
		GPIO_Pin1 = GPIO_Pin_4;
		GPIO_Pin2 = GPIO_Pin_6;
		GPIO_Pin3 = GPIO_Pin_4;
	}

	if(channel == 0)
	{
		GPIO_ResetBits(GPIO1,GPIO_Pin1);
		GPIO_ResetBits(GPIO2,GPIO_Pin2);
		GPIO_ResetBits(GPIO3,GPIO_Pin3);			
	}
	else if(channel == 1)
	{
		GPIO_ResetBits(GPIO1,GPIO_Pin1);
		GPIO_ResetBits(GPIO2,GPIO_Pin2);
		GPIO_SetBits(GPIO3,GPIO_Pin3);
	}
	else if(channel == 2)
	{
		GPIO_ResetBits(GPIO1,GPIO_Pin1);
		GPIO_SetBits(GPIO2,GPIO_Pin2);
		GPIO_ResetBits(GPIO3,GPIO_Pin3);
	}
	else if(channel == 3)
	{
		GPIO_ResetBits(GPIO1,GPIO_Pin1);
		GPIO_SetBits(GPIO2,GPIO_Pin2);
		GPIO_SetBits(GPIO3,GPIO_Pin3);
	}
}


void CD4051_Switch_Down(u8 channel,u8 switchs)
{
	GPIO_TypeDef* GPIO1;
	GPIO_TypeDef* GPIO2;
	GPIO_TypeDef* GPIO3;
	uint16_t GPIO_Pin1,GPIO_Pin2,GPIO_Pin3;
	
	if(switchs==1)
	{
		GPIO1 = GPIOE;
		GPIO2 = GPIOE;
		GPIO3 = GPIOE;
		GPIO_Pin1 = GPIO_Pin_0;
		GPIO_Pin2 = GPIO_Pin_2;
		GPIO_Pin3 = GPIO_Pin_4;
	}
	else if(switchs==2)
	{
		GPIO1 = GPIOF;
		GPIO2 = GPIOF;
		GPIO3 = GPIOF;
		GPIO_Pin1 = GPIO_Pin_0;
		GPIO_Pin2 = GPIO_Pin_2;
		GPIO_Pin3 = GPIO_Pin_4;
	}

	else if(switchs==3)
	{
		GPIO1 = GPIOF;
		GPIO2 = GPIOF;
		GPIO3 = GPIOC;
		GPIO_Pin1 = GPIO_Pin_8;
		GPIO_Pin2 = GPIO_Pin_10;
		GPIO_Pin3 = GPIO_Pin_1;
	}
	else if(switchs==4)
	{
		GPIO1 = GPIOA;
		GPIO2 = GPIOA;
		GPIO3 = GPIOA;
		GPIO_Pin1 = GPIO_Pin_0;
		GPIO_Pin2 = GPIO_Pin_5;
		GPIO_Pin3 = GPIO_Pin_7;
	}

	if(channel == 0)
	{
		GPIO_ResetBits(GPIO1,GPIO_Pin1);
		GPIO_ResetBits(GPIO2,GPIO_Pin2);
		GPIO_ResetBits(GPIO3,GPIO_Pin3);			
	}
	else if(channel == 1)
	{
		GPIO_ResetBits(GPIO1,GPIO_Pin1);
		GPIO_ResetBits(GPIO2,GPIO_Pin2);
		GPIO_SetBits(GPIO3,GPIO_Pin3);
	}
	else if(channel == 2)
	{
		GPIO_ResetBits(GPIO1,GPIO_Pin1);
		GPIO_SetBits(GPIO2,GPIO_Pin2);
		GPIO_ResetBits(GPIO3,GPIO_Pin3);
	}
	else if(channel == 3)
	{
		GPIO_ResetBits(GPIO1,GPIO_Pin1);
		GPIO_SetBits(GPIO2,GPIO_Pin2);
		GPIO_SetBits(GPIO3,GPIO_Pin3);
	}
}




