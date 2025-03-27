#ifndef __BSP_LED_H
#define __BSP_LED_H
#include "stm32f10x.h"

#define LED1_OFF         GPIO_ResetBits(GPIOD, GPIO_Pin_0)
#define LED1_ON          GPIO_SetBits(GPIOD, GPIO_Pin_0)

#define LED6_OFF         GPIO_ResetBits(GPIOD, GPIO_Pin_1)
#define LED6_ON          GPIO_SetBits(GPIOD, GPIO_Pin_1)

#define LED1_BLUE_TOGGLE (GPIO_ToggleBits(GPIOD, GPIO_Pin_0)) // 反转，电平取反
#define LED6_BLUE_TOGGLE (GPIO_ToggleBits(GPIOD, GPIO_Pin_0)) 

void LED_Init(void);

#endif