#ifndef __BASIC_H
#define __BASIC_H
#include "stm32f10x.h"

/* 电机基础动作 */

void Start(void);
void Run(int run_speed);
void Run_delay(int run_speed, uint16_t last_time);
void run(int left_speed, int right_speed);
void run_delay(int left_speed, int right_speed, uint16_t last_time);
void stop(void);
void Stop(uint16_t times);
void Right_Speed_Down(int Fir, int End, uint16_t delay_time);
void Left_Speed_Down(int Fir, int End, uint16_t delay_time);
void Right_Speed_Up(int Fir, int End, uint16_t delay_time);
void Left_Speed_Up(int Fir, int End, uint16_t delay_time);
void turnR_speed_up(int Low, int High, uint16_t delay_time);
void turnR_speed_down(int High, int Low, uint16_t delay_time);
void turnL_speed_up(int Low, int High, uint16_t delay_time);
void turnL_speed_down(int High, int Low, uint16_t delay_time);

#endif