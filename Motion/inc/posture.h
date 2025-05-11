#ifndef __POSTURE_H
#define __POSTURE_H
#include "stm32f10x.h"

#define outline       (Huidu_va(0) < 200 && Huidu_va(1) < 200 && Huidu_va(2) < 200 && Huidu_va(3) < 200 && Huidu_va(4) < 200 && Huidu_va(5) < 200 && Huidu_va(6) < 200 && Huidu_va(7) < 200 && Huidu_va(8) < 200 && Huidu_va(9) < 200 && Huidu_va(10) < 200 && Huidu_va(11) < 200)
#define Detect_NoLine Huidu_va(0) < 200 && Huidu_va(1) < 200 && Huidu_va(2) < 200 && Huidu_va(3) < 200 && Huidu_va(4) < 200 && Huidu_va(5) < 200 && \
                          Huidu_va(6) < 200 && Huidu_va(7) < 200 && Huidu_va(8) < 200 && Huidu_va(9) < 200 && Huidu_va(10) < 200 &&                 \
                          Huidu_va(11) < 200

void Front_down(void);
void Front_mid(void);
void Front_up(void);
void Front_up_High(void);
void Paw_open(void);
void Paw_close(void);
void Camera_down(void);
void Camera_down_low(void);
void Camera_up(void);
void Camera_up_hight(void);
void Catch(void);
void down_pt1_6(void);
void UP_Tai2_6(void);
void UP_Tai2_6_noline(void);
void UP_Tai2(void);
void UP_Tai7(void);
void Down_Tai7(void);
void UP_Tai8(void);
void Down_Tai8(void);
void Bridge_Travel(void);
void drift_left(int speed, uint8_t model);
void drift_right(int speed, uint8_t model);
void drift_right_2(int speed, uint8_t model);
void Drift_Rightpass_BLB(void);
void Past_Seesaw(int time_stop, int time_Seesaw);
void Land_Protect_adjust(void);
void Seesaw_with_Adjustion(int time_stop, int time_Seesaw);
void Back_BLB(void);
void txs(void);
void Go_BLB(void);
void Get_Traget_Color(void);
void Get_Now_Color(void);
void Get_QR(void);
void Get_Turn(void);

#endif