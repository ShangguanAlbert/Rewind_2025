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
    GPIO_HW_Init();
    GPIO_HDLR_Init();
    pid_init(&pid_yaw, 55, 10, 4, 2, 3);
    Set_PID_turn_params(&pid_comp_params, 2.8, 0, 5, 10);

    progg = Function_Mode();
    if (progg == 1) {
        down_pt1_6();//下台
        Front_mid();
        Reset(30, 60);
        while (hdxl != 0) {
            drift_right(70, 0);
        }
        Reset(400,70);

        while (hdxl != 0) {
            slow_run(50);
        }
        Reset(1600,50);
        TurnRight_135_Longline();
        Reset(600,60);
        Reset(1200,135);
        Reset(400,70);
        UP_Tai2_6();
    
        
       
    }
    if (progg == 2) {
       /* Stop(3000);
        //Reset(50, 30);
        //speed_up(40, 120);
        Reset(100,60);
        Reset(80,110);
        Reset(1000, 170);
        //Run_delay(170,2700);
        speed_down(120, 30);
        */
       down_pt1_6();//下台
    Front_mid();
    Reset(30, 60);
    while (hdxl != 0) {
        drift_right(70, 0);
    }
    Reset(400,70);

     while (hdxl != 0) {
        slow_run(50);
    }
    Reset(1600,50);
    Reset_drift_left(70,0,500);
    Reset(100,70);
    Reset(1500,130);
    Reset(650,60);
    UP_Tai2_6();
    }
    if (progg == 3) {
        Tai1_Tai2();
    }
    if (progg == 4) {
        Bridge_Travel();
    }
    if (progg == 5) {
         bridge_PD(30,1);
    }
    if (progg == 6) {
        UP_Tai2_6();
    }
    if (progg == 7) {
        Stop(3000);
        speed_up(30, 60);
        Reset(2500,105);
        speed_down(60,30);
    }
    if (progg == 8) {
        Show_SensorPage_All();
    }
    stop();
    while (1) {};
}