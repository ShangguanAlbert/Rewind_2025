#ifndef __BSP_SENSOR_H
#define __BSP_SENSOR_H
#include "stm32f10x.h"

#define hwr  HW(1)
#define hwl  HW(2)
#define hdxr  HDLR(1)
#define hdxl  HDLR(2)

void GPIO_HW_Init(void);
uint8_t HW(uint8_t LR);
void GPIO_HDLR_Init(void);
uint8_t HDLR(uint8_t LR);
void GPIO_LED_Init(void);

#endif // !__BSP_SENSOR_H