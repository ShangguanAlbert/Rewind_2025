#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "lcd_spi_130.h"
#include "bsp_lcd_test.h"
#include "bsp_adc.h"
#include "bsp_key.h"
#include "bsp_lcd.h"
#include "bsp_led.h"
#include "bsp_compass.h"
#include "bsp_motor.h"
#include "bsp_vision.h"
#include "bsp_servo.h"
#include "basic.h"

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
    LED_Init();
    KEY_Init();
    progg = Function_Mode();

    if (progg == 1) {
        Run_delay(110, 2000);
    }
    if (progg == 2) {
        Run_delay(60,500);
        Run_delay(120, 1900);
        Run_delay(60, 500);
    }
    if (progg == 3) {
        Run_delay(60,400);
        Run_delay(135, 1900);
        Run_delay(60, 400);
    }
    if (progg == 4) {
        Run_delay(60,400);
        Run_delay(150, 1800);
        Run_delay(60, 400);
    }
    if (progg == 5) {
        Run_delay(60,400);
        Run_delay(160, 1700);
        Run_delay(60, 400);
    }
    if (progg == 6) {
        Run_delay(60,400);
        Run_delay(170, 1600);
        Run_delay(100, 100);
        Run_delay(50, 300);
    }
    if (progg == 7) {
        Run_delay(60,400);
        Run_delay(180, 1600);
        Run_delay(100, 100);
        Run_delay(50, 400);
    }
    if (progg == 8) {
        // Run_delay(60,300);
        // Run_delay(120,300);
        // Run_delay(190, 1500);
        // Run_delay(100, 100);
        // Run_delay(50, 400);
        Show_SensorPage_All();
    }
    stop();
    while (1) {};
}