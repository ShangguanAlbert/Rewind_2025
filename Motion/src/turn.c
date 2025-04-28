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
void TurnLeft_135_Longline(void)
{
    while (1) {
        slow_run(50);
        if (Huidu_va(11) > white[11] || Huidu_va(10) > white[10]) {
            break;
        }
    }
    Right_Speed_Up(50, 115, 3);
    Left_Speed_Down(50, -90, 4);
    while (1) {
        run(-65, 85);
        if (Huidu_va(6) > white[6] || Huidu_va(5) > white[5]) {
            break;
        }
    }
}
void TurnLeft_135_Longline2(void)
{
    while (1) {
        slow_run(50);
        if (Huidu_va(11) > white[11] || Huidu_va(10) > white[10]) {
            break;
        }
    }
    Right_Speed_Up(50, 115, 4);
    Left_Speed_Down(50, -90, 4);
    while (1) {
        run(-65, 90);
        if (Huidu_va(6) > white[6] || Huidu_va(5) > white[5]) {
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
        run(x * 0.86, -x * 0.94);
        Delay_ms(8); //
    }
    pid_Turn(500);
    Stop(50);
    Front_down();
}
void Tai2_zhuan90(void)
{
    Stop(100);
    HWT101_to_0();
    Stop(250);
    Front_up_High();
    Deg_IN();
    for (int x = 55; x < 85; x++) {
        run(x * 0.94, -x * 0.89);
        Delay_ms(8); //
    }
    pid_Turn_Right90(500);
    Stop(50);
    Front_down();
}
/**
 * @brief 中平台掉头转180
 *
 */
void Tai7_zhuan(void)
{
    Front_up_High();
    Stop(100);
    HWT101_to_0();
    Stop(250);
    Deg_IN();
    for (int x = 45; x <= 118; x++) {
        run(x * 0.92, -x * 1.25); // 0.95,1.2
        delay_ms(8);
    }
    pid_Turn(1200);
    stop();
    Front_down();
}
/**
 * @brief 高平台掉头转180
 *
 */
void Tai8_zhuan(void)
{
    Front_up_High();
    Stop(100);
    HWT101_to_0();
    Stop(250);

    Deg_IN();
    for (int x = 40; x < 95; x++) {
        run(x * 0.8, -x * 2); // 1.05
        delay_ms(9);
    }
    for (int x = 40; x > 95; x--) {
        run(x * 0.8, -x * 2);
        delay_ms(9);
    }
    pid_Turn(1100);
    stop();
    Front_down();
    Stop(300);
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
 * @brief 右转90度,左灰度
 */
void TurnRight_90_Ldetect(void)
{
    while (1) {
        slow_run(50);
        if (Huidu_va(11) > white[11] || Huidu_va(10) > white[10] || Huidu_va(9) > white[9]) {
            break;
        }
    }
    Left_Speed_Up(50, 85, 5);
    Right_Speed_Down(50, -75, 5);
    while (1) {
        run(75, -70);
        if (Huidu_va(4) > white[4] || Huidu_va(5) > white[5]) {
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
        if (Huidu_va(11) > white[11] || Huidu_va(10) > white[10] || Huidu_va(9) > white[9]) {
            break;
        }
    }
    // 左转
    Right_Speed_Up(50, 80, 5);
    Left_Speed_Down(50, -80, 5);
    while (1) {
        run(-85, 80);
        if (Huidu_va(6) > white[6] || Huidu_va(7) > white[7]) {
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
        if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1] || Huidu_va(2) > white[2]) {
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
    run_delay(70, -73, 50);
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
        slow_run(60);
        if (Huidu_va(11) > white[11] || Huidu_va(10) > white[10] || Huidu_va(9) > white[9]) {
            break;
        }
    }
    // 左转
    Right_Speed_Up(50, 80, 5);
    Left_Speed_Down(50, -80, 5);
    while (1) {
        run(-75, 70);
        if (Huidu_va(6) > white[6] || Huidu_va(7) > white[7]) {
            break;
        }
    }
    run_delay(-75, 76, 50);
    while (1) {
        run(-75, 76);
        if (Huidu_va(6) > white[6] || Huidu_va(7) > white[7]) {
            break;
        }
    }
}

/**
 * @brief 左转90度 右灰度检测(2)
 *
 */
void TurnLeft_90_Rdetect_in2(void)
{
    // 检测左转
    while (1) {
        slow_run(60);
        if (Huidu_va(11) > white[11] || Huidu_va(10) > white[10] || Huidu_va(9) > white[9]) {
            break;
        }
    }
    // 左转
    Right_Speed_Up(50, 80, 5);
    Left_Speed_Down(50, -80, 5);
    while (1) {
        run(-75, 70);
        if (Huidu_va(6) > white[6] || Huidu_va(7) > white[7]) {
            break;
        }
    }
    run_delay(-75, 72, 50);
    while (1) {
        run(-75, 72);
        if (Huidu_va(6) > white[6] || Huidu_va(7) > white[7]) {
            break;
        }
    }
}

/**
 * @brief 左转90度，左腰灯检测
 *
 */
void TurnLeft_90_hdxlDetect(void)
{
    while (1) {
        slow_run(50);
        if (hdxl == 0) {
            break;
        }
    }

    Right_Speed_Up(50, 80, 5);
    Left_Speed_Down(50, -80, 5);

    while (1) {
        run(-50, 50);
        if (Huidu_va(6) > white[6] || Huidu_va(5) > white[5]) {
            break;
        }
    }
}

/**
 * @brief 下台8左转90度，左灰度检测两次
 *
 */
void TurnLeft_90_Ldetect_tai8(void)
{
    while (1) {
        slow_run(50);
        if (Huidu_va(10) > white[10]) {
            break;
        }
    }
    while (1) {
        slow_run(50);
        if (Huidu_va(10) < white[10]) {
            break;
        }
    }
    while (1) {
        slow_run(50);
        if (Huidu_va(10) > white[10]) {
            break;
        }
    }

    Right_Speed_Up(50, 95, 5);
    Left_Speed_Down(50, -90, 5);
    while (1) {
        run(-75, 75);
        if (Huidu_va(6) > white[6] || Huidu_va(7) > white[7]) {
            break;
        }
    }
}
/**
 * @brief 下台8左转90度，右灰度检测
 *
 */
void TurnLeft_90_Rdetect_tai8(void)
{
    while (1) {
        slow_run(50);
        if (Huidu_va(1) > white[1] || Huidu_va(0) > white[0]) {
            break;
        }
    }

    Right_Speed_Up(50, 95, 5);
    Left_Speed_Down(50, -90, 5);
    while (1) {
        run(-75, 75);
        if (Huidu_va(6) > white[6] || Huidu_va(7) > white[7]) {
            break;
        }
    }
}
/**
 * @brief 台8回家走完波浪板后右转
 *
 */
void TurnRight_90_Ldetect_1(void)
{
    while (1) {
        slow_run(50);
        if (Huidu_va(11) > white[11] || Huidu_va(10) > white[10] || Huidu_va(9) > white[9]) {
            break;
        }
    }
    Left_Speed_Up(50, 90, 5);
    Right_Speed_Down(50, -70, 5);
    while (1) {
        run(80, -65);

        if (Huidu_va(4) > white[4] || Huidu_va(5) > white[5]) {
            break;
        }
    }
}
/**
 * @brief 出t型山，转90度
 *
 */
void Out_T_TurnRight_90(void)
{
    while (1) {
        Run(50);
        if (Huidu_va(10) > white[10] || Huidu_va(11) > white[11]) {
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
 * @brief 出t型山，转90度
 *
 */
void Out_T_TurnLeft_90(void)
{
    while (1) {
        Run(50);
        if (Huidu_va(10) > white[10] || Huidu_va(11) > white[11]) {
            break;
        }
    }
    Right_Speed_Up(50, 95, 5);
    Left_Speed_Down(50, -90, 5);
    while (1) {
        run(-75, 75);
        if (Huidu_va(6) > white[6] || Huidu_va(7) > white[7]) {
            break;
        }
    }
}
/**
 * @brief 转90度,进t型山
 *
 */
void In_T_TurnLeft_90(void)
{
    while (1) {
        Run(50);
        if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1]) {
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
