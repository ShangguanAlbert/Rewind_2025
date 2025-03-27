#ifndef __BSP_COMPASS_H
#define __BSP_COMPASS_H
#include "stm32f10x.h"
#include "stdio.h"
#include <string.h>
#include "stdlib.h"
#include "math.h"

extern float JD;

typedef struct {
    short Angle[3];
    short T;
} SAngle;

extern SAngle stcAngle;

void USART2_COMPASS_Init(void);
void CopeSerial2Data(unsigned char ucData);
void HWT101_to_0(void);
float compass_b(void);

#endif