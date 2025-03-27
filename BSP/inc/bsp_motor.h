#ifndef __BSP_MOTOR_H
#define __BSP_MOTOR_H
#include "stm32f10x.h"

void TIM8_Motor_Init(void);
void Motor(uint8_t port, int speed);
void set_pwm(uint8_t port, int speed, int set_speed);
float m_diff(int speed);
#endif