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

extern int32_t white[];
extern int32_t green[];
extern int32_t thr_whiteline[];

void get_huidu_va(void);
void Trace(void);
void Trace_transVelocity(void);
void high_run(int N);
void slow_run(int N);
void slow_run1(int N);
void speed_up(int start, int end);
void speed_down(int high, int low);
void speed_up_high(int start, int end);
void speed_down_high(int start, int end);
void bridge_Trace(uint8_t mode);
void bridge_PD(int N, uint8_t mode);
void Straight_run(int speed);
void Straight_back(void);
void Straight_run_back(int speed);
void txs_trace(void);
void Straight(int time);

#endif