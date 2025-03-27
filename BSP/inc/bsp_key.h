#ifndef __BSP_KEY_H
#define __BSP_KEY_H
#include "stm32f10x.h"

#define KeyUp      GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10)
#define KeyDown    GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)
#define KeyConfirm GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11)

void KEY_Init(void);
uint8_t KEY_Scan(uint8_t mode);

#endif