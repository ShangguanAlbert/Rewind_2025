#ifndef __ROUTE_H
#define __ROUTE_H
#include "stm32f10x.h"

#define outline (Huidu_va(0) < 200 && Huidu_va(1) < 200 && Huidu_va(2) < 200 && Huidu_va(3) < 200 && Huidu_va(4) < 200 && Huidu_va(5) < 200 && Huidu_va(6) < 200 && Huidu_va(7) < 200 && Huidu_va(8) < 200 && Huidu_va(9) < 200 && Huidu_va(10) < 200 && Huidu_va(11) < 200)

void Tai1_Tai2(void);
void Tai2_Tai3(void);
void Tai2_Tai4(void);
void Tai3_door1_Tai5(void);
void Tai3_door2_Tai5(void);
void Tai3_door3_Tai5(void);
void Tai3_door4_Tai5(void);
void Tai4_Tai5(void);
void Tai5_Tai7(void);
void Tai5_Tai8(void);
void Tai7_Home(void);
void Tai8_Home(void);
void txs(void);

#endif