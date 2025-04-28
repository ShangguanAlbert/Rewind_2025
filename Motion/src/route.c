
#include "route.h"
#include "reset.h"
#include "posture.h"
#include "trace.h"
#include "bsp_adc.h"
#include "bsp_servo.h"
#include "bsp_sensor.h"
#include "bsp_SysTick.h"
#include "turn.h"

void Tai1_Tai2(void)
{
    // 下台
    down_pt1_6();
    // 矫正
    Reset(650, 60); //
    // 过桥
    Bridge_Travel();
    // 加速
    speed_up(60, 130);
    speed_down(130, 60);

    UP_Tai2_6();
    //
}

void Tai2_Tai3(void)
{
    down_pt1_6(); // 下台
    Reset(60, 60);
    while (hdxl != 0) {
        drift_right(70, 0);
    }
    Reset(320, 60);

    while (hdxl != 0) {
        slow_run(45);
    }
    Reset(1600, 45);
    TurnRight_135_Longline();
    Stop(50);
    Reset(250, 70);
    speed_up(70, 190);
    Reset(150, 190);
    speed_down(190, 50);
    UP_Tai2_6();
}

void Tai2_Tai4(void)
{
    down_pt1_6(); // 下台
    Reset(60, 60);
    while (hdxl != 0) {
        drift_right(70, 0);
    }
    Reset(320, 60);

    while (hdxl != 0) {
        slow_run(45);
    }
    Reset(1600, 45);
    Reset_drift_left(70, 0, 800);
    Reset(250, 70);
    speed_up(70, 190);
    Reset(150, 190);
    speed_down(190, 50);
    UP_Tai2_6();
}
// void Tai3_Tai5(void)
// {
//     down_pt1_6();
//     Reset(200, 70);
//     Reset(800, 120);
//     Reset(200, 70);
//     Reset_drift_right(70, 0, 500);
// }

/*
下台3从门2通过
*/
void Tai3_door2_Tai5(void)
{
    down_pt1_6();

    Reset(100, 70);
    speed_up(70, 160);
    speed_down(160, 70);
    while (1) {
        slow_run(70);
        if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1]) {
            break;
        }
    }
    Reset_drift_right(70, 0, 700);
    Reset(100, 70);
    speed_up(70, 175);
    speed_down(175, 50);
    while (1) {
        slow_run(70);
        if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1]) {
            break;
        }
    }

    Reset_drift_left(70, 0, 500);
    Reset(250, 70);
    speed_up(70, 150);
    speed_down(150, 50);
    UP_Tai2_6();
}

/*
下台三右转进门1
*/
// void Tai3_door1_Tai5(void)
// {
//     down_pt1_6();
//     Reset(200,70);
//     Reset(1000,120);
//     Reset(300,70);
//     //右转90度
//     TurnRight_90_Rdetect_in();
//     Stop(50);
//     Reset(200,50);
//     Reset(200,70);
//     Reset(850,115);
//     Reset(300,70);
// TurnLeft_90_Ldetect();
// Stop(30);
// Reset(200,70);
// Reset(900,120);
// Reset(400,135);
// Reset(900,120);
// Reset(200,70);

// TurnLeft_90_Ldetect();
// Reset(400,70);

// while (hdxl != 0) {
//    slow_run(50);}

// }

/*
下台3转门3，要转两次
 */
void Tai3_door3_Tai5(void)
{
    // down_pt1_6();
    // Reset(200,70);
    // Reset(2400,120);
    // Reset(500,70);
    TurnRight_135_Longline();
}

/*
下台3一直直走右转进门4
*/
void Tai3_door4_Tai5(void)
{
    // down_pt1_6();
    // Reset(200,70);
    // Reset(2400,120);
    // Reset(500,70);
    TurnRight_90_hdxrDetect();
    Stop(40);
    // Reset(300,70);
    // Reset(500,120);
    // Reset(400,70);
    // TurnLeft_90_Rdetect();
    // Stop(40);
    // Reset(200,70);
    // Reset(800,120);
    // Reset(400,70);
    // UP_Tai2_6();
}
/*
台4到台5
*/
void Tai4_Tai5(void)
{
    down_pt1_6();
    Reset(100, 70);
    speed_up(70, 170);
    speed_down(170, 70);
    TurnLeft_90_Rdetect_in();
    Stop(40);
    Reset(250, 70);
    speed_up(70, 150);
    speed_down(150, 50);
    TurnLeft_90_Rdetect_in2();
    Stop(50);
    Reset(350, 70);
    speed_up(70, 160);
    speed_down(160, 70);
    UP_Tai2_6();
}

void Tai5_Tai7(void)
{
    down_pt1_6();
    Reset(200, 50);
    speed_up(50, 190);
    Reset(200, 190);
    speed_down(190, 50);
    TurnLeft_90_Rdetect();
    Stop(40);
    while (1) {
        slow_run(50);
        if (hwr == 0) {
            break;
        }
    }
    Front_down();
    Reset(1400, 50);
    Front_mid();
    Reset(200, 50);
    // speed_up(50, 100);
    // speed_down(100, 50);
    // TurnLeft_90_Rdetect();
    // Stop(40);

    Stop(40);

    Reset(250, 60);
    speed_up(60, 185);
    speed_down(185, 50);
    UP_Tai7();
}
void Tai5_Tai8(void)
{
    down_pt1_6();
    Reset(200, 50);
    speed_up(50, 190);
    Reset(200, 190);
    speed_down(190, 50);
    TurnLeft_90_Rdetect();
    Stop(40);
    while (1) {
        slow_run(50);
        if (hwr == 0) {
            break;
        }
    }
    Front_down();
    Reset(1400, 50);
    Front_mid();
    Reset(200, 50);
    // speed_up(50,100);
    // speed_down(100,50);
    // TurnRight_90_Ldetect();
    Out_T_TurnRight_90();
    Stop(40);
    Reset(250, 70);
    speed_up(70, 140);
    speed_down(140, 50);
    UP_Tai8();
}
/*
台7回家
*/
void Tai7_Home(void)
{
    //放下前铲
    Front_down();
    Stop(400);
    //下台7
    Down_Tai7();
    //巡线修正
    Reset(500, 50);
    //开始向右漂移直到左腰灯检测到白线
    while (hdxl != 0) {
        drift_right_2(70, 1);
    }
    //上跷跷板前检测
    while (hwr == 1) {
        high_run(70);
    }
    //过跷跷板
    Seesaw_with_Adjustion(900, 2100);
    //修正
    Reset(400, 70);
    //巡线直到右灰度等测到白线
    while (1) {
        high_run(90);
        if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1]) {
            break;
        }
    }
    //左侧腰灯检测到白线，向右漂移
    while (hdxl == 1) {
        drift_right(90, 1);
    }
    //修正
    Reset(300, 70);
    //加速
    speed_up(70, 140);
    speed_down(140, 70);
    //左转90度
    TurnLeft_90_Rdetect_tai8();
    Stop(100);
    //修正
    Reset(250, 50);
    //加速
    speed_up(50, 120);
    speed_down(120, 50);
    //修正
    Reset(60, 60);
    while (hdxr != 0) {
        drift_right(50, 0);
    }
    Reset(500, 45);

    Back_BLB();
    TurnRight_135_Longline();
    Stop(50);
    Reset(250, 50);
    speed_up(50, 100);
    speed_down(100, 50);
    Bridge_Travel();
    Reset(600, 60);
    UP_Tai2_6();
}
/*
台8回家
*/
void Tai8_Home(void)
{
    //放下前铲
    Front_down();
    Stop(300);
    //下台8
    Down_Tai8();
    //巡线
    Reset(200, 40);
    speed_up(40, 140);
    speed_down(140, 50);
    //左转135度
    TurnLeft_135_Longline();
    Stop(50);
    //确认上跷跷板
    while (hwr == 1) {
        high_run(70);
    }
    //过跷跷板
    Seesaw_with_Adjustion(900, 2100);
    //巡线修正
    Reset(350, 70);
    //向右漂移 
    Reset_drift_right(70,1,800);
    //加速
    speed_up(70,160);
    //减速
    speed_down(160,50);
    //向右转90度（左测灰度灯检测转弯起始点）
    TurnRight_90_Ldetect();
    Stop(50);
    //加速
    speed_up(45,120);
    //减速
    speed_down(120,50);
    //向左转135度
    TurnLeft_135_Longline2();
    //回程过波浪板
    Back_BLB();
    //右转135
    TurnRight_135_Longline();
    Stop(50);
    //巡线修正
    Reset(250, 50);
    speed_up(50, 100);
    speed_down(100, 50);
    //桥上巡线
    Bridge_Travel();
    Reset(600, 60);
    //上台1
    UP_Tai2_6();
}