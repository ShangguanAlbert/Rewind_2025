#ifndef __RESET_H
#define __RESET_H
#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_motor.h"
#include "trace.h"
#include "basic.h"
#include "bsp_timer.h"

void Reset(int time_last, int goal_speed);
void Reset_bridge(int time_last, int goal_speed, uint8_t mode);

#endif