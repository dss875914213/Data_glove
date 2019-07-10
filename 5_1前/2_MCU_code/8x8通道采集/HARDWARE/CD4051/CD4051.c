/*
Switch1_Up_A:			0
Switch1_Up_B:			C9
Switch1_Up_C:			C8
Switch1_Up_INH: 	C7
Switch1_Down_A:		0
Switch1_Down_B:		C6
Switch1_Down_C:		B0
Switch1_Down_INH:	B1

Switch2_Up_A:			0
Switch2_Up_B:			B2
Switch2_Up_C:			B3
Switch2_Up_INH: 	B4
Switch2_Down_A:		0
Switch2_Down_B:		B5
Switch2_Down_C:		B6
Switch2_Down_INH:	B7

Switch3_Up_A:			0
Switch3_Up_B:			B8
Switch3_Up_C:			B9
Switch3_Up_INH: 	B10
Switch3_Down_A:		0
Switch3_Down_B:		B11
Switch3_Down_C:		B12
Switch3_Down_INH:	B13

Switch4_Up_A:			0
Switch4_Up_B:			B14
Switch4_Up_C:			B15
Switch4_Up_INH: 	C10
Switch4_Down_A:		0
Switch4_Down_B:		C3
Switch4_Down_C:		C2
Switch4_Down_INH:	C0



b3  b4
*/
#include "CD4051.h"

void CD4051_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);//使能PORTA,PORTC时钟

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_All;//PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOC5
	GPIO_ResetBits(GPIOB,GPIO_Pin_All);
	
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_13;//PA15
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOA15
	GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_13);

}

void CD4051_Switch_Up(u8 channel,u8 chip)
{

	GPIO_TypeDef* GPIO_A;
	GPIO_TypeDef* GPIO_B;
	uint16_t GPIO_PinA,GPIO_PinB;
	
	if(chip==1)
	{

		GPIO_A = GPIOC;
		GPIO_B = GPIOC;

		GPIO_PinA = GPIO_Pin_9;
		GPIO_PinB = GPIO_Pin_8;
	}
	else if(chip==2)
	{

		GPIO_A = GPIOB;
		GPIO_B = GPIOB;

		GPIO_PinA = GPIO_Pin_2;
		GPIO_PinB = GPIO_Pin_3;
	}
	else if(chip==3)
	{

		GPIO_A = GPIOB;
		GPIO_B = GPIOB;

		GPIO_PinA = GPIO_Pin_8;
		GPIO_PinB = GPIO_Pin_9;
	}
	else if(chip==4)
	{

		GPIO_A = GPIOB;
		GPIO_B = GPIOB;
		
		GPIO_PinA = GPIO_Pin_14;
		GPIO_PinB = GPIO_Pin_15;
	}

	if(channel == 0)
	{
		GPIO_ResetBits(GPIO_B,GPIO_PinB);
		GPIO_ResetBits(GPIO_A,GPIO_PinA);		
	}
	else if(channel == 1)
	{	
		GPIO_ResetBits(GPIO_B,GPIO_PinB);
		GPIO_SetBits(GPIO_A,GPIO_PinA);
	}
	else if(channel == 2)
	{
		GPIO_SetBits(GPIO_B,GPIO_PinB);
		GPIO_ResetBits(GPIO_A,GPIO_PinA);
		
	}
	else if(channel == 3)
	{
		GPIO_SetBits(GPIO_B,GPIO_PinB);
		GPIO_SetBits(GPIO_A,GPIO_PinA);		
	}
}


void CD4051_Switch_Down(u8 channel,u8 chip)
{

	GPIO_TypeDef* GPIO_A;
	GPIO_TypeDef* GPIO_B;
	uint16_t GPIO_PinA,GPIO_PinB;
	
	if(chip==1)
	{
		GPIO_A = GPIOC;
		GPIO_B = GPIOB;

		GPIO_PinA = GPIO_Pin_6;
		GPIO_PinB = GPIO_Pin_0;
	}
	else if(chip==2)
	{

		GPIO_A = GPIOB;
		GPIO_B = GPIOB;

		GPIO_PinA = GPIO_Pin_5;
		GPIO_PinB = GPIO_Pin_6;
	}
	else if(chip==3)
	{		
		GPIO_A = GPIOB;
		GPIO_B = GPIOB;

		GPIO_PinA = GPIO_Pin_11;
		GPIO_PinB = GPIO_Pin_12;
	}
	else if(chip==4)
	{
		GPIO_A = GPIOC;
		GPIO_B = GPIOC;
		
		GPIO_PinA = GPIO_Pin_3;
		GPIO_PinB = GPIO_Pin_2;
	}

	if(channel == 0)
	{
		GPIO_ResetBits(GPIO_B,GPIO_PinB);
		GPIO_ResetBits(GPIO_A,GPIO_PinA);		
	}
	else if(channel == 1)
	{	
		GPIO_ResetBits(GPIO_B,GPIO_PinB);
		GPIO_SetBits(GPIO_A,GPIO_PinA);
	}
	else if(channel == 2)
	{
		GPIO_SetBits(GPIO_B,GPIO_PinB);
		GPIO_ResetBits(GPIO_A,GPIO_PinA);
		
	}
	else if(channel == 3)
	{
		GPIO_SetBits(GPIO_B,GPIO_PinB);
		GPIO_SetBits(GPIO_A,GPIO_PinA);		
	}
}



