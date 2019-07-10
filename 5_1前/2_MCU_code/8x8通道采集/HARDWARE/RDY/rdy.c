#include "rdy.h"


void RDY_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTC时钟

	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入

 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOC5
	GPIO_SetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_3);

}




