#include "turn.h"
#include "trace.h"
#include "bsp_adc.h"
#include "posture.h"
#include "bsp_SysTick.h"
#include "bsp_compass.h"
#include "reset.h"
#include "pid_turn.h"
#include "bsp_servo.h"
#include "bsp_sensor.h"
#include "basic.h"

void TurnRight_135_Longline(void)
{
    while (1) {
        slow_run(50);
        if (Huidu_va(1) > white[1] || Huidu_va(0) > white[0]) {
            break;
        }
    }
    Left_Speed_Up(50, 115, 3);
    Right_Speed_Down(50, -90, 4);
    while (1) {
        run(85, -65);
        if (Huidu_va(4) > white[4] || Huidu_va(5) > white[5]) {
            break;
        }
    }
}


void Tai1_6_zhuan(void)
{
    Stop(100);
    HWT101_to_0();
    Stop(250);
    Front_up_High();
    Deg_IN();
    for (int x = 55; x < 110; x++) {
        run(x * 1.0, -x * 0.92);
        Delay_ms(8); //
    }
    pid_Turn(500);
    Stop(50);
    Front_down();
}

/**
 * @brief 右转90度
 */
void TurnRight_90_Rdetect(void)
{
    while (1) {
        slow_run(50);
        if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1] || Huidu_va(2) > white[2]) {
            break;
        }
    }
    Left_Speed_Up(50, 90, 5);
    Right_Speed_Down(50, -85, 5);
    while (1) {
        run(70, -73);
        if (Huidu_va(6) > white[6] || Huidu_va(5) > white[5]) {
            break;
        }
    }
}
/**
 * @brief 左转90度 右灰度检测
 *
 */
void TurnLeft_90_Rdetect(void)
{
    // 检测左转
    while (1) {
        slow_run(50);
        if (Huidu_va(11) > white [11]|| Huidu_va(10) > white[10] || Huidu_va(9) > white[9]) {
            break;
        }
    }
    // 左转
    Right_Speed_Up(50, 80, 5);
    Left_Speed_Down(50, -80, 5);
    while (1) {
        run(-85, 80);
        if (Huidu_va(6) > white [6]|| Huidu_va(7) > white[7]) {
            break;
        }
    }
}

/**
 * @brief 左转90度 左灰度检测
 *
 */
void TurnLeft_90_Ldetect(void)
{
    while (1) {
        slow_run(50);
        if (Huidu_va(0) > white[0] || Huidu_va(1) > white [1]|| Huidu_va(2) > white[2]) {
            break;
        }
    }
    Right_Speed_Up(50, 95, 5);
    Left_Speed_Down(50, -85, 5);
    while (1) {
        run(-70, 80);
        if (Huidu_va(8) > white[8] || Huidu_va(7) > white[7]) {
            break;
        }
    }
}

void TurnRight_90_hdxrDetect(void)
{
    while (hdxr == 1) {
        slow_run(50);
    }

    Right_Speed_Down(50, -90, 6);
    Left_Speed_Up(50, 90, 5);

    while (1) {
        run(65, -50);
        if (Huidu_va(6) > white[6] || Huidu_va(7) > white[7]) {
            break;
        }
    }
}

/**
 * @brief 右转90度
 */
void TurnRight_90_Rdetect_in(void)
{
    while (1) {
        slow_run(50);
        if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1] || Huidu_va(2) > white[2]) {
            break;
        }
    }
    Left_Speed_Up(50, 90, 5);
    Right_Speed_Down(50, -85, 5);
    while (1) {
        run(70, -73);
        if (Huidu_va(6) > white[6] || Huidu_va(5) > white[5]) {
            break;
        }
    }
    run_delay(70, -73,50);
    while (1) {
        run(70, -73);
        if (Huidu_va(5) > white[5] || Huidu_va(4) > white[4]) {
            break;
        }
    }
    
}

/**
 * @brief 左转90度 右灰度检测
 *
 */
void TurnLeft_90_Rdetect_in(void)
{
    // 检测左转
    while (1) {
        slow_run(50);
        if (Huidu_va(11) > white [11]|| Huidu_va(10) > white[10] || Huidu_va(9) > white[9]) {
            break;
        }
    }
    // 左转
    Right_Speed_Up(50, 80, 5);
    Left_Speed_Down(50, -80, 5);
    while (1) {
        run(-75, 70);
        if (Huidu_va(6) > white [6]|| Huidu_va(7) > white[7]) {
            break;
        }
    }
    run_delay(-75,70,50);
    while (1) {
        run(-75, 70);
        if (Huidu_va(6) > white [6]|| Huidu_va(7) > white[7]) {
            break;
        }
    }
}
