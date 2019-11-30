#ifndef __BEEP_H
#define __BEEP_H	 
#include "stm32f10x.h"


//BEEP端口定义
#define beep PBout(1)// PB1

void BEEP_Init(void);//初始化

		 				    
#endif
