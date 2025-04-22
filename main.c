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
#include "bsp_sensor.h"
#include "basic.h"
#include "trace.h"
#include "reset.h"
#include "pid_turn.h"
#include "posture.h"
#include "route.h"
#include "turn.h"
#include "bsp_qr.h"

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
    UART4_QRCode_Init();
    TIM2_Servo_Init();
    TIM3_TurnPID_Init();
    TIM7_Reset_Init();
    LED_Init();
    KEY_Init();
    GPIO_HW_Init();
    GPIO_HDLR_Init();
    pid_init(&pid_yaw, 55, 10, 4, 2, 3);
    Set_PID_turn_params(&pid_comp_params, 2.8, 0, 5, 10);

    progg = Function_Mode();
    if (progg == 1) {
        Tai2_zhuan90();
        Stop(3000);
        Tai2_zhuan90();
    }
    if (progg == 2) {
        Tai7_zhuan();
    }
    if (progg == 3) {
        Tai8_zhuan();
    }
    if (progg == 4) {
        Run_delay(50, 200);
        Run_delay(80, 100);
        Run_delay(110, 1400);
        Run_delay(80, 100);
        Run_delay(50, 200);
    }
    if (progg == 5) {
        // 二维码扫描模式
        LCD_Clear(); // 清屏，黑色背景
        while (1) {
            QR_Process();  // 处理二维码数据
            delay_ms(100); // 延时100ms，避免刷新过快
        }
    }
    if (progg == 6) {
        UP_Tai2_6();
    }
    if (progg == 7) {
        Stop(3000);
        speed_up(30, 60);
        Reset(2500, 105);
        speed_down(60, 30);
    }
    if (progg == 8) {
        Show_SensorPage_All();
    }
    stop();
    while (1) {};
}