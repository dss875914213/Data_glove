#include "rdy.h"


void RDY_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTCʱ��

	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������

 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOC5
	GPIO_SetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_3);

}




