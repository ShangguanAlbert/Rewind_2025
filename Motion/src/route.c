
#include "route.h"
#include "reset.h"
#include "posture.h"
#include "trace.h"
#include "bsp_adc.h"
#include "bsp_servo.h"
#include "bsp_sensor.h"
#include "bsp_SysTick.h"
#include "turn.h"
#include "bsp_compass.h"

/**
 * @brief 台一到台二
 * 
 */
void Tai1_Tai2(void)
{
    // 下台1
    down_pt1_6();
    // 矫正
    Reset(650, 60); 
    // 过桥
    Bridge_Travel();
    // 加速
    speed_up(60, 130);
    speed_down(130, 60);
    //减速

    UP_Tai2_6();
    //上低平台2
}

/**
 * @brief 台二到台三
 * 
 */
void Tai2_Tai3(void)
{
    down_pt1_6(); // 下台2
    Reset(60, 60);//巡线
    while (hdxl != 0) {
        drift_right(70, 0);
    }
    Reset(320, 60);
    //向右飘移直到左腰灯扫到白线后低速巡线


    while (hdxl != 0) {
        slow_run(45);
    }


    Reset(1600, 45);//巡线
    TurnRight_135_Longline();//右转135度进台三
    Stop(50);
    Reset(250, 70);//巡线
    speed_up(70, 190);//加速
    Reset(150, 190);//巡线
    speed_down(190, 50);//减速
    UP_Tai2_6();//上台3
}

/**
 * @brief 台2进台4
 * 
 */
void Tai2_Tai4(void)
{
    down_pt1_6(); // 下台2
    Reset(60, 60);//巡线
    while (hdxl != 0) {
        drift_right(70, 0);
    }
    Reset(320, 60);
//向右飘移直到左腰灯扫到白线后低速巡线


    while (hdxl != 0) {
        slow_run(45);
    }


    Reset(1600, 45);//巡线
    Reset_drift_left(70, 0, 800);//向左飘进台4
    Reset(250, 70);//巡线
    speed_up(70, 190);//加速
    Reset(150, 190);//巡线
    speed_down(190, 50);//减速
    UP_Tai2_6();//上台4
}


/*
下台3从门2通过到台5
*/
void Tai3_door2_Tai5(void)
{
    down_pt1_6();//下台3
    Reset(100, 70);//巡线
    speed_up(70, 160);//加速
    speed_down(160, 70);//减速
    while (1) {
        slow_run(70);
        if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1]) {
            break;
        }
    }
    Reset_drift_right(70, 0, 700);//当灰度01检测到白线时向右飘
    Reset(100, 70);//巡线
    speed_up(70, 175);//加速
    speed_down(175, 50);//减速

    while (1) {
        slow_run(70);
        if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1]) {
            break;
        }
    }
    Reset_drift_left(70, 0, 500);//当灰度01检测到白线时向左飘

    Reset(250, 70);//巡线
    speed_up(70, 150);//加速
    speed_down(150, 50);//减速
    UP_Tai2_6();//上台5
}

/*
台4到台5
*/
void Tai4_Tai5(void)
{
    down_pt1_6();//下台4
    Reset(100, 70);//巡线
    speed_up(70, 170);//加速
    speed_down(170, 70);//减速
    TurnLeft_90_Ldetect_4();//左转90度
    Stop(40);
    Reset(250, 70);//巡线
    speed_up(70, 150);//加速
    speed_down(150, 50);//减速
    TurnLeft_90_Ldetect_5();//左转90度
    Stop(50);
    Reset(350, 70);//巡线
    speed_up(70, 160);//加速
    speed_down(160, 70);//减速
    UP_Tai2_6();//上台5
}


/**
 * @brief 台五到台七
 * 
 */
void Tai5_Tai7(void)
{
    down_pt1_6();//下台5
    Reset(200, 50);//巡线
    speed_up(50, 190);//加速
    Reset(200, 190);//巡线
    speed_down(190, 50);//减速
    TurnLeft_90_Ldetect_Mountain();//左转进梯形山
    Stop(40);



    // // while (1) {
    // //     slow_run(50);
    // //     if (hwr == 0) {
    // //         break;
    // //     }
    // // }
    // // Front_down();
    // // Reset(1400, 50);
    // // Front_mid();
    // // Reset(200, 50);
    // // speed_up(50, 100);
    // // speed_down(100, 50);


    
    txs();//上梯形山后无白线直走
    TurnLeft_90_Ldetect();//左转
    Stop(40);

    Reset(250, 60);//巡线
    speed_up(60, 185);//加速
    speed_down(185, 50);//减速
    UP_Tai7();//上台7
}


/**
 * @brief 台5到台8
 * 
 */
void Tai5_Tai8(void)
{
    down_pt1_6();//下台五
    Reset(200, 50);//巡线
    speed_up(50, 190);//加速
    Reset(200, 190);//巡线
    speed_down(190, 50);//减速
    TurnLeft_90_Ldetect_Mountain();//左转进梯形山
    Stop(40);


    // while (1) {
    //     slow_run(50);
    //     if (hwr == 0) {
    //         break;
    //     }
    // }
    // Straight(5000);
    // Stop(40);


    txs();//梯形山无白线直走
    Out_T_TurnRight_90();//右转进台8
    Stop(40);
    Reset(250, 70);//巡线
    speed_up(70, 140);//加速
    speed_down(140, 50);//减速
    UP_Tai8();//上台8
}



/*
台7回家
*/
void Tai7_Home(void)
{
    // 放下前铲
    Front_down();
    Stop(400);
    // 下台7
    Down_Tai7();
    // 巡线修正
    Reset(500, 50);
    // 开始向右漂移直到左腰灯检测到白线
    while (hdxl != 0) {
        drift_right_2(70, 1);
    }
    // 上跷跷板前检测
    while (hwr == 1) {
        high_run(70);
    }
    // 过跷跷板
    Seesaw_with_Adjustion(900, 2100);
    // 修正
    Reset(400, 70);
    // 巡线直到右灰度等测到白线
    while (1) {
        high_run(90);
        if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1]) {
            break;
        }
    }
    // 左侧腰灯检测到白线，向右漂移
    while (hdxl == 1) {
        drift_right(90, 1);
    }
    // 修正
    Reset(300, 70);
    // 加速
    speed_up(70, 140);
    speed_down(140, 70);
    // 左转90度
    TurnLeft_90_Rdetect_4();
    Stop(100);
    // 修正
    Reset(250, 50);
    // 加速
    speed_up(50, 120);
    speed_down(120, 50);
    // 修正
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
    // 放下前铲
    Front_down();
    Stop(300);
    // 下台8
    Down_Tai8();
    // 巡线
    Reset(200, 40);
    speed_up(40, 140);
    speed_down(140, 50);
    // 左转135度
    TurnLeft_135_Longline();
    Stop(50);
    // 确认上跷跷板
    while (hwr == 1) {
        high_run(70);
    }
    // 过跷跷板
    Seesaw_with_Adjustion(900, 2100);
    // 巡线修正
    Reset(350, 70);
    // 向右漂移
    Reset_drift_right(70, 1, 800);
    // 加速
    speed_up(70, 160);
    // 减速
    speed_down(160, 50);
    // 向右转90度（左测灰度灯检测转弯起始点）
    TurnRight_90_Ldetect_3();
    Stop(50);
    // 加速
    speed_up(45, 120);
    // 减速
    speed_down(120, 50);
    // 向左转135度
    TurnLeft_135_Longline2();
    // 回程过波浪板
    Back_BLB();
    // 右转135
    TurnRight_135_Longline();
    Stop(50);
    // 巡线修正
    Reset(250, 50);
    speed_up(50, 100);
    speed_down(100, 50);
    // 桥上巡线
    Bridge_Travel();
    Reset(600, 60);
    // 上台1
    UP_Tai2_6();
}