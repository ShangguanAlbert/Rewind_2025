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

/**
 * @brief 右转135°后进长桥（用于回家和台2-台3）
 *
 */
void TurnRight_135_Longline(void)
{
    // 低速巡线，当灰度0，1扫到白线时候跳出循环，开始转弯
    while (1) {
        slow_run(50);
        if (Huidu_va(1) > white[1] || Huidu_va(0) > white[0]) {
            break;
        }
    }
    Left_Speed_Up(50, 115, 3);
    Right_Speed_Down(50, -90, 4);
    while (1) {
        // 左右轮设定不同速度，直到灰度4，5扫到白线
        run(85, -65);
        if (Huidu_va(4) > white[4] || Huidu_va(5) > white[5]) {
            break;
        }
    }
}

/**
 * @brief 左转135度（进台八回家的翘翘板）
 *
 */
void TurnLeft_135_Longline(void)
{
    // 低速巡线，当灰度10，11扫到白线时候跳出循环，开始转弯
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

/**
 * @brief 左转135度进波浪板
 *
 */
void TurnLeft_135_Longline2(void)
{
    // 低速巡线，当灰度10，11扫到白线时候跳出循环，开始转弯进波浪板
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

/**
 * @brief 低平台转180度
 *
 */
void Tai1_6_zhuan(void)
{
    Stop(100);
    HWT101_to_0();
    Stop(250);
    Front_up_High();
    Stop(400);
    Deg_IN();
    for (int x = 70; x < 110; x++) {
        run(x * 0.86, -x * 0.94);
        Delay_ms(12); // 加速
    }
    // for (int x = 110; x > 60; x--) {
    //     run(x * 0.86, -x * 0.94);
    //     Delay_ms(2); //加速
    // }
    // run_delay(90,-90*m_diff(90),350);

    pid_Turn(800);
    // Stop(50);
    // Front_down();
}
/**
 * @brief 低平台转180度
 *
 */
void Tai1_6_zhuan1(void)
{
    Stop(100);
    HWT101_to_0();
    Stop(250);
    Front_up_High();
    Stop(400);
    Deg_IN();
    run_delay(150, -150, 200);
    pid_Turn(800);
}

void turn_around_180(void)
{
    int g         = 0; // 是否进行了旋转
    int angle_now = 0; // 当前角度，初始化为0
    Front_up_High();
    Stop(300);
    angle_now = compass_b(); // 获取当前角度
    while (g < 1) {
        if (angle_now >= 0 && angle_now < 180) {
            run_delay(-75, 75, 600);
            while (compass_b() < (165 + angle_now)) {
                run(-50, 50);
            }
            g++;
        } else if (angle_now >= 180 && angle_now < 360) {
            run_delay(60, -60, 600);
            while (compass_b() > (angle_now - 162)) {
                run(40, -40);
            }
            g++;
        }
    }
    Front_mid();
    Stop(400);
}

/**
 * @brief 台2转九十度1
 *
 */
void Tai2_zhuan90_1(void)
{
    Stop(100);
    HWT101_to_0();
    Stop(250);
    Front_up_High();
    Deg_IN();
    for (int x = 55; x < 85; x++) {
        run(x * 0.90, -x * 0.89); // 98
        Delay_ms(8);              //
    }
    pid_Turn_Right90(500);
    Stop(50);
    // Front_down();
}
/**
 * @brief 台2转九十度2
 *
 */
void Tai2_zhuan90_2(void)
{
    Stop(100);
    HWT101_to_0();
    Stop(250);
    Front_up_High();
    Deg_IN();
    for (int x = 55; x < 85; x++) {
        run(x * 0.90, -x * 0.89); // 98
        Delay_ms(8);              //
    }
    pid_Turn_Right90(500);
    Stop(50);
    Front_down();
}
/**
 * @brief 左转25度
 *
 */
void Turn_Left25(void)
{
    Stop(100);
    HWT101_to_0();
    Stop(250);
    Deg_IN();
    run(-30, 30); // 98
    Delay_ms(50);
    Stop(10); //
    pid_Turn_Left25(500);
    Stop(50);
}
void Turn_Left22(void)
{
    Stop(100);
    HWT101_to_0();
    Stop(250);
    Deg_IN();
    run(-30, 30); // 98
    Delay_ms(50);
    Stop(10); //
    pid_Turn_Left22(500);
    Stop(50);
}
/**
 * @brief 右转25度
 *
 */
void Turn_Right25(void)
{
    Stop(100);
    HWT101_to_0();
    Stop(250);
    Deg_IN();
    run(30, -30); // 98
    Delay_ms(50);
    Stop(10); //
    pid_Turn_Right25(500);
    Stop(50);
}
/**
 * @brief 右转50度
 *
 */
void Turn_Right50(void)
{
    Stop(100);
    HWT101_to_0();
    Stop(250);
    Deg_IN();
    run(30, -30); // 98
    Delay_ms(50);
    Stop(10); //
    pid_Turn_Right50(1000);
    Stop(50);
}
/**
 * @brief 中平台掉头转180
 *
 */
void Tai7_zhuan(void)
{
    // Front_up_High();
    // Stop(100);
    // HWT101_to_0();
    // Stop(250);
    // Deg_IN();
    // for (int x = 45; x <= 118; x++) {
    //     run(x * 0.90, -x * 1.4); // 0.95,1.2
    //     delay_ms(8);
    // }
    // pid_Turn(1200);
    // stop();
    // Front_down();

    Front_up_High();
    Stop(100);
    HWT101_to_0();
    Stop(250);
    Deg_IN();
    for (int x = 55; x < 110; x++) {
        run(x * 0.86, -x * 0.94);
        Delay_ms(8); //
    }
    pid_Turn(500);
    Stop(50);
    Front_down();
}
/**
 * @brief 八平台掉头转180
 *
 */
void Tai8_zhuan(void)
{
    // Front_up_High();
    // Stop(100);
    // HWT101_to_0();
    // Stop(400);

    // Deg_IN();
    // for (int x = 40; x < 80; x++) {
    //     run(x * 0.8, -x * 1.8); // 1.05
    //     delay_ms(20);
    // }
    // for (int x = 40; x > 80; x--) {
    //     run(x * 0.8, -x * 1.8);
    //     delay_ms(20);
    // }
    // pid_Turn(1000);
    // stop();
    // Front_down();
    // Stop(300);

    Front_up_High();
    Stop(100);
    HWT101_to_0();
    Stop(250);
    Deg_IN();
    for (int x = 60; x < 110; x++) {
        run(x * 0.86, -x * 0.90);
        Delay_ms(5);
    }
    pid_Turn(800);
    Stop(50);
    Front_down();
    Stop(300);
}

// void Tai8_zhuan(void) {
//      int g = 0;
//      //static int gqJD;
//      float gqJD = compass_b();
//      Stop(50);
//      Front_up_High();
//      delay_ms(200);
//      //run(20, -20);
//      //delay_ms(450);
//      while (g < 1)
//      {
//       if (gqJD <= 180 && gqJD>=0)
//       {
//        run_delay(-60,60,450);
//        while (compass_b() < (170+gqJD))
//        {
//         if(compass_b() - gqJD < 120)
//         run(-60,60);
//         else if(compass_b() - gqJD > 140)
//         run(-40,40);
//         else
//         run((compass_b() - gqJD) - 180 ,180 - (compass_b() - gqJD));
//        }
//        g++;
//       }
//       else if (gqJD > 180 && gqJD <= 360)
//       {
//        run_delay(60,-60,450);
//        while (compass_b() > (gqJD-170))
//        {
//         if(gqJD - compass_b() < 120)
//         run(60,-60);
//         else if(gqJD - compass_b() > 140)
//         run(40,-40);
//         else
//         run(180-(gqJD - compass_b()) , (gqJD - compass_b())-180);
//        }
//        g++;
//       }
//       else
//        while (compass_b() < 180)
//        {
//         run(40, -40);
//        }
//       g++;
//      }
//      stop();
//      Front_down();
//      Delay_ms(200);
//     }

/**
 * @brief 右转90度，左灰度
 */
void TurnRight_90_Rdetect(void)
{
    // 检测
    while (1) {
        slow_run(50);
        if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1] || Huidu_va(2) > white[2]) {
            break;
        }
    }
    // 转弯
    Left_Speed_Up(50, 90, 5);
    Right_Speed_Down(50, -85, 5);
    while (1) {
        run(70, -73);
        // 检测停止
        if (Huidu_va(6) > white[6] || Huidu_va(5) > white[5]) {
            break;
        }
    }
}
/**
 * @brief 右转90度,左灰度
 */
void TurnRight_90_Ldetect_3(void)
{
    // 低速巡线，当灰度9，10，11扫到白线时候跳出循环，开始转弯
    while (1) {
        slow_run(50);
        if (Huidu_va(11) > white[11] || Huidu_va(10) > white[10] || Huidu_va(9) > white[9]) {
            break;
        }
    }
    // 转弯
    Left_Speed_Up(50, 85, 5);
    Right_Speed_Down(50, -75, 5);
    while (1) {
        run(75, -70);
        // 检测停止
        if (Huidu_va(4) > white[4] || Huidu_va(5) > white[5]) {
            break;
        }
    }
}
/**
 * @brief 左转90度 左灰度检测
 *        用于台5左转上梯形山
 */
void TurnLeft_90_Ldetect_Mountain(void)
{
    // 左灰度灯检测左转
    while (1) {
        slow_run(50);
        if (Huidu_va(11) > white[11] || Huidu_va(10) > white[10] || Huidu_va(9) > white[9]) {
            break;
        }
    }
    // 左转
    Right_Speed_Up(50, 85, 5);
    Left_Speed_Down(50, -75, 5);
    while (1) {
        run(-80, 85);
        // 检测停止
        if (Huidu_va(6) > white[6] || Huidu_va(7) > white[7]) {
            break;
        }
    }
}

/**
 * @brief 左转90度上台7 左灰度检测
 *
 */
void Out_T_TurnLeft_90_Ldetect(void)
{
    // 低速巡线，当灰度10，11扫到白线时候跳出循环，开始转弯
    while (1) {
        slow_run(50);
        if (Huidu_va(10) > white[10] || Huidu_va(11) > white[11] || Huidu_va(9) > white[9]) {
            break;
        }
    }
    // 转弯
    Right_Speed_Up(50, 95, 5);
    Left_Speed_Down(50, -85, 5);
    while (1) {
        run(-70, 80);
        // 检测停止
        if (Huidu_va(8) > white[8] || Huidu_va(7) > white[7]) {
            break;
        }
    }
}

/**
 * @brief 右转90度，右腰灯检测
 *
 */
void TurnRight_90_hdxrDetect(void)
{
    // 检测
    while (hdxr == 1) {
        slow_run(50);
    }
    // 转弯
    Right_Speed_Down(50, -90, 6);
    Left_Speed_Up(50, 90, 5);
    // 检测停止
    while (1) {
        run(65, -50);
        if (Huidu_va(6) > white[6] || Huidu_va(7) > white[7]) {
            break;
        }
    }
}

/**
 * @brief 右转90度，检测到第二条白线后停止
 */
void TurnRight_90_Rdetect_in(void)
{
    // 检测
    while (1) {
        slow_run(50);
        if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1] || Huidu_va(2) > white[2]) {
            break;
        }
    }
    // 转弯
    Left_Speed_Up(50, 90, 5);
    Right_Speed_Down(50, -85, 5);
    // 第一次检测到白线后继续转弯
    while (1) {
        run(70, -73);
        if (Huidu_va(6) > white[6] || Huidu_va(5) > white[5]) {
            break;
        }
    }
    run_delay(70, -73, 50);
    // 第二次检测后停止
    while (1) {
        run(70, -73);
        if (Huidu_va(5) > white[5] || Huidu_va(4) > white[4]) {
            break;
        }
    }
}

/**
 * @brief 左转90度 左灰度检测
 *        用于台4进门4
 */
void TurnLeft_90_Ldetect_4(void)
{
    // 左边白线灰度灯检测左转
    while (1) {
        slow_run(60);
        if (Huidu_va(11) > white[11] || Huidu_va(10) > white[10] || Huidu_va(9) > white[9]) {
            break;
        }
    }
    // 左转
    Right_Speed_Up(50, 80, 5);
    Left_Speed_Down(50, -80, 5);
    // 扫到第一根白线继续转
    while (1) {
        run(-75, 70);
        if (Huidu_va(6) > white[6] || Huidu_va(7) > white[7]) {
            break;
        }
    }
    run_delay(-75, 76, 50);
    // 左转，扫到第二根白线停止
    while (1) {
        run(-75, 76);
        if (Huidu_va(6) > white[6] || Huidu_va(7) > white[7]) {
            break;
        }
    }
}

/**
 * @brief 左转90度 左灰度检测
 *        用于门4进台5
 */
void TurnLeft_90_Ldetect_5(void)
{
    // 左灰度灯检测左转
    while (1) {
        slow_run(60);
        if (Huidu_va(11) > white[11] || Huidu_va(10) > white[10] || Huidu_va(9) > white[9]) {
            break;
        }
    }
    // 左转检测到第一条白线继续转
    Right_Speed_Up(50, 80, 5);
    Left_Speed_Down(50, -80, 5);
    while (1) {
        run(-75, 70);
        if (Huidu_va(6) > white[6] || Huidu_va(7) > white[7]) {
            break;
        }
    }
    run_delay(-75, 72, 50);
    // 左转检测到第二条白线停止转弯
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
    // 检测
    while (1) {
        slow_run(50);
        if (hdxl == 0) {
            break;
        }
    }
    // 转弯
    Right_Speed_Up(50, 80, 5);
    Left_Speed_Down(50, -80, 5);
    // 检测停止
    while (1) {
        run(-50, 50);
        if (Huidu_va(6) > white[6] || Huidu_va(5) > white[5]) {
            break;
        }
    }
}

/**
 * @brief 下台8左转90度，左灰度检测两次（无法使用）
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
 * @brief 左转90度，右灰度检测
 *        用于右边直接扫到水平白线
 *
 */
void TurnLeft_90_Rdetect_4(void)
{
    // 低速巡线，当灰度0，1扫到白线时候跳出循环，开始转弯
    while (1) {
        slow_run(50);
        if (Huidu_va(1) > white[1] || Huidu_va(0) > white[0]) {
            break;
        }
    }
    // 转弯
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
 * @brief 台8回家走完波浪板后右转（无法使用）
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
 * @brief 出t型山，右转90度进台8
 *
 */
void Out_T_TurnRight_90_Ldetect(void)
{
    // 检测
    while (1) {
        Run(50);
        if (Huidu_va(10) > white[10] || Huidu_va(11) > white[11]) {
            break;
        }
    }
    // 转弯
    Left_Speed_Up(50, 90, 5);
    Right_Speed_Down(50, -88, 5);
    // 检测转正
    while (1) {
        run(70, -75);
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
    // 低速巡线，当灰度0，1扫到白线时候跳出循环，开始转弯
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
