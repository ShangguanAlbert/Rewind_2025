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

extern int32_t white[];
extern int8_t OpenMV;
extern float JD;
extern float XJD;
extern float GJD;
extern float MJD;
extern float WJD;
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
    USART5_OpenMV_Init();
    UART4_QRCode_Init();
    TIM2_Servo_Init();
    TIM3_TurnPID_Init();
    TIM7_Reset_Init();
    LED_Init();
    KEY_Init();
    GPIO_HW_Init();
    GPIO_HDLR_Init();
    // pid_init(&pid_yaw, 60, 10, 2, 1.5, 10);
    pid_init(&pid_yaw, 60, 10, 3.6, 2, 3);
    pid_init(&pid_yaw1, 60, 10, 4, 2, 3);
    // Set_PID_turn_params(&pid_comp_params, 2.8, 0, 5, 10);

    progg = Function_Mode();
    if (progg == 1) {
        UP_Tai2_6_noline();
        Stop(250);
        Front_down();
        Stop(200);
        while (1) {
            slow_run(45);
            if (hwr == 0) break;
        }
        Reset(300, 45);
        Stop(300);
        Straight_back();
        Treasure_Locator2();
        // Right_Catch();
        // Treasure_Locator3();
    }
    if (progg == 2) {
        Camera_down();
    }

    if (progg == 3) {
        Camera_down();
        Stop(1000);
        // Turn_Right25();
        Detect_Color();
        Get_Traget_Color();
    }
    if (progg == 4) {
        Turn_Left25();
        Stop(1000);
        Turn_Right50();
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
        Tai8_zhuan();
    }
    if (progg == 7) {
        Camera_up_hight();
    }
    if (progg == 8) {
        // while (1) {
        //     Deg_IN();
        //     LCD_SetDirection(Direction_H_Flip);
        //     LCD_ShowNumMode(Fill_Space);
        //     LCD_DisplayString(5, 35, "JD:");
        //     LCD_DisplayNumber(70, 35, JD, 4);
        //     LCD_DisplayString(5, 60, "XJD:");
        //     LCD_DisplayNumber(70, 60, XJD, 4);
        //     LCD_DisplayString(5, 85, "GJD:");
        //     LCD_DisplayNumber(70, 85, GJD, 4);
        //     LCD_DisplayString(5, 110, "MJD:");
        //     LCD_DisplayNumber(70, 110, MJD, 4);
        //     LCD_DisplayString(5, 135, "WJD:");
        //     LCD_DisplayNumber(70, 135, WJD, 4);
        // };
        Show_SensorPage_All();
    }
    stop();
    while (1) {};
}