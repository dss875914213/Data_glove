#ifndef __CD4051_H
#define __CD4051_H

#include "sys.h"

void CD4051_Init(void);
void CD4051_Switch_Up(u8 channel,u8 switchs);
void CD4051_Switch_Down(u8 channel,u8 switchs);

#define Switch1_Up_INH PCout(7)	
#define Switch2_Up_INH PBout(4)	
#define Switch3_Up_INH PBout(10)	
#define Switch4_Up_INH PCout(10)	

#define Switch1_Down_INH PBout(1)	
#define Switch2_Down_INH PBout(7)	
#define Switch3_Down_INH PBout(13)	
#define Switch4_Down_INH PCout(0)	

#define Switch_On  0
#define Switch_Off 1

#endif




