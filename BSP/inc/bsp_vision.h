#ifndef __BSP_VISION_H
#define __BSP_VISION_H
#include "stm32f10x.h"

#define cmd      0xb5
#define treasure openmv[2]

extern int openmv[];
void USART5_OpenMV_Init(void);
void Openmv_Data(void);
void Openmv_Receive_Data(int16_t data);
void Detect_Color(void);
void Locate_treasure(void);
void SHUT_UP(void);

#endif