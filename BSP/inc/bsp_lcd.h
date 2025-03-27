#ifndef __BSP_LCD_H
#define __BSP_LCD_H
#include "stm32f10x.h"
#include "lcd_spi_130.h"
#include "bsp_SysTick.h"

void Show_SensorPage_All(void);
void Sensor_Test_Page1(void);
void Sensor_Test_Page2(void);
uint8_t Function_Mode(void);

#endif