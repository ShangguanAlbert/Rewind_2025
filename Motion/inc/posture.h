#ifndef __POSTURE_H
#define __POSTURE_H
#include "stm32f10x.h"

void Front_down(void);
void Front_mid(void);
void Front_up(void);
void Front_up_High(void);
void down_pt1_6(void);
void UP_Tai2_6(void);
void UP_Tai7(void);
void Down_Tai7(void);
void UP_Tai8(void);
void Down_Tai8(void);
void Bridge_Travel(void);
void drift_left(int speed, uint8_t model);
void drift_right(int speed, uint8_t model);
void Drift_Rightpass_BLB(void);
void Past_Seesaw(int time_stop, int time_Seesaw);
void Land_Protect_adjust(void);


#endif