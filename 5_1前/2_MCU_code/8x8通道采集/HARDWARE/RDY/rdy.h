#ifndef __RDY_H
#define __RDY_H

#include "sys.h"

void RDY_Init(void);

#define RDY0  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)
#define RDY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)


#endif




