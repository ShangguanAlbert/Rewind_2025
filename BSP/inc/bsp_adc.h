#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "stm32f10x.h"

void ADC1_Huidu_Init(void);
uint32_t Filter(uint16_t num);
int32_t Huidu_va(uint8_t ch);


#endif // __BSP_ADC_H__