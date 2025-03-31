#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H
#include "stm32f10x.h"

extern uint32_t t3_i;
extern uint32_t t7_i;

void TIM3_TurnPID_Init(void);
void TIM7_Reset_Init(void);

#endif