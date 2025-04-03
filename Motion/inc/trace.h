#ifndef __TRACE_H
#define __TRACE_H
#include "stm32f10x.h"
#include "basic.h"
#include "bsp_motor.h"
#include "bsp_SysTick.h"
#include "bsp_timer.h"
#include "bsp_adc.h"

#define thr_line  {250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250}
#define thr_white {200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200}
#define thr_green {130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130}

void get_huidu_va(void);
void Trace(void);
void high_run(int N);
void slow_run(int N);
void speed_up(int start, int end);
void speed_down(int high, int low);

#endif