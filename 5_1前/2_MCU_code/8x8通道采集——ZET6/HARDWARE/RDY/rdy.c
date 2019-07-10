#include "rdy.h"


void RDY_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTC时钟

	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3;//PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOC5
	GPIO_SetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_3);

}




