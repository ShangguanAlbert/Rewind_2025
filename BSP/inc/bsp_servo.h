#ifndef __BSP_SERVO_H
#define __BSP_SERVO_H
#include "stm32f10x.h"

void TIM2_Servo_Init(void);
void Servo_SetAngle(uint8_t channel, uint16_t angle);

#endif