#ifndef __BSP_SYSTICK_H
#define __BSP_SYSTICK_H
#include "stm32f10x.h"

void SysTick_Init(void);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_s(uint32_t s);

#endif // __BSP_SYSTICK_H