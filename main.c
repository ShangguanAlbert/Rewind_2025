#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "lcd_spi_130.h"
#include "bsp_lcd_test.h"
#include "bsp_adc.h"
#include "bsp_key.h"
#include "bsp_lcd.h"
#include "bsp_led.h"
#include "bsp_compass.h"
#include "bsp_timer.h"
#include "bsp_motor.h"
#include "bsp_vision.h"
#include "bsp_servo.h"
#include "basic.h"
#include "trace.h"
#include "reset.h"

uint8_t prog_num_hope = 8;

uint8_t progg;

int main(void)
{
    SysTick_Init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    ADC1_Huidu_Init();
    TIM8_Motor_Init();
    SPI_LCD_Init();
    USART2_COMPASS_Init();
    USART3_OpenMV_Init();
    TIM2_Servo_Init();
    TIM3_TurnPID_Init();
    TIM7_Reset_Init();
    LED_Init();
    KEY_Init();
    progg = Function_Mode();
    if (progg == 1) {
        Stop(3000);
        speed_up(60, 120);
        Reset(3300, 120);
        speed_down(120, 50);
    }
    if (progg == 2) {
        Stop(3000);
        speed_up(60, 130);
        Reset(3500, 130);
        speed_down(130, 50);
    }
    if (progg == 3) {
        speed_up(60, 120);
        // Reset(500, 120);
        speed_down(120, 50);
    }
    if (progg == 4) {
        Reset(2000, 70);
    }
    if (progg == 5) {
    }
    if (progg == 6) {
    }
    if (progg == 7) {
    }
    if (progg == 8) {
        Show_SensorPage_All();
    }
    stop();
    while (1) {};
}