#include "route.h"
#include "reset.h"
#include "posture.h"
#include "trace.h"
#include "bsp_adc.h"
#include "bsp_servo.h"
#include "bsp_sensor.h"
#include "bsp_SysTick.h"
#include "turn.h"
#include "bsp_lcd.h"
#include "bsp_vision.h"
#include "bsp_qr.h"
#include "bsp_compass.h"
#include "pid_turn.h"
extern int8_t Traget_Color;
extern int8_t NOW_Color;
extern int8_t Turn_Or_Not;
extern uint8_t cnt_whiteline;
/**
 * @brief 无抓宝全程，走台
 */
void all_6(void)
{
    TurnRight_135_Circle();
    Reset_drift_left(60, 0, 600);
    Touch_Seesaw_adjust();
    Seesaw_with_Adjustion(1100, 2200);
    Land_Protect_adjust();
    // 检测左转
    while (1) {
        slow_run(50);
        if (Huidu_va(10) > white[10] || Huidu_va(9) > white[9]) {
            break;
        }
    }
    // 左转
    // 左转
    Right_Speed_Up(50, 95, 5);
    Left_Speed_Down(50, -90, 5);
    while (1) {
        run(-75, 80);
        if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1]) {
            break;
        }
    }
    while (1) {
        run(-75, 80);
        if (Huidu_va(6) > white[6] || Huidu_va(5) > white[5]) {
            break;
        }
    }
    Stop(80);
    // 抓宝
    UP_Tai2_6_noline();
    down_pt1_6();
    TurnLeft_90_Rdetect_4();
    Stop(50);
    Touch_Seesaw_adjust();
    Seesaw_with_Adjustion(1100, 2200);
    Land_Protect_adjust();
    while (1) {
        drift_left(60, 0);
        if (hdxr == 0) {
            break;
        }
    }
    while (1) {
        drift_right(60, 0);
        if (Huidu_va(11) > white[11] || Huidu_va(10) > white[10]) {
            break;
        }
    }
    Stop(100);
    while (1) {
        run(-30, 30);
        if (Huidu_va(5) > white[5] || Huidu_va(4) > white[4]) {
            break;
        }
    }
    Stop(50);
    Reset(110, 60);
}
/**
 * @brief 台4到台6
 *
 */
void all_4_door1_6(void)
{
    Reset(100, 70);
    // 加速
    speed_up(70, 170);
    speed_down(170, 70);
    while (1) {
        slow_run(70);
        if (Huidu_va(10) > white[0] || Huidu_va(11) > white[1]) {
            break;
        }
    }
    Reset_drift_left(70, 0, 500);
    Reset(500, 50);
    while (hdxl != 0 || hdxr != 0) {
        slow_run(50);
    }
    Reset(800, 50);
    speed_up(50, 120);
    Reset(500, 120);
    speed_down(120, 50);
    while (1) {
        slow_run(70);
        if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1]) {
            break;
        }
    }
    // 向右漂移一段时间，过弯
    Reset_drift_right(70, 0, 500);
    Reset(500, 70);
    all_6();
}
/**
 * @brief 台3到台6
 *
 */
void all_3_door1_6(void)
{
    Reset(100, 70);
    // 加速
    speed_up(70, 140);
    speed_down(140, 70);
    TurnRight_90_Rdetect_3_indoor1();
    Reset(250, 50);
    speed_up(50, 95);
    speed_down(95, 50);
    while (hdxl != 0 || hdxr != 0) {
        slow_run(50);
    }
    Reset(1200, 50);
    TurnRight_90_Rdetect();
    Stop(50);
    Reset(1000, 60);
    all_6();
   
}
/**
 * @brief 无抓宝全程
 */
void all_3_5(void)
{
    Tai1_Tai2();
    UP_Tai2_6_noline();
    down_pt1_6();
    Tai2_Tai3();
    UP_Tai2_6_noline();
    down_pt1_6();
    Tai3_door2_Tai5();
    UP_Tai2_6_noline();
    down_pt1_6();
    Tai5_Home();
}
/**
 * @brief 无抓宝全程
 */
void all_3_6(void)
{
    Tai1_Tai2();
    UP_Tai2_6_noline();
    down_pt1_6();
    Tai2_Tai3();
    UP_Tai2_6_noline();
    down_pt1_6();
    all_3_door1_6();
    Tai6_Home();
}
/**
 * @brief 无抓宝全程
 */
void all_4_5(void)
{
    Tai1_Tai2();
    UP_Tai2_6_noline();
    down_pt1_6();
    Tai2_Tai4();
    UP_Tai2_6_noline();
    down_pt1_6();
    Tai4_door4_Tai5();
    UP_Tai2_6_noline();
    down_pt1_6();
    Tai5_Home();
}

/**
 * @brief 无抓宝全程
 */
void all_4_6(void)
{
    Tai1_Tai2();
    UP_Tai2_6_noline();
    down_pt1_6();
    Tai2_Tai4();
    UP_Tai2_6_noline();
    down_pt1_6();
    Tai4_door3_Tai6();
    Tai6_Home();
}

/**
 * @brief 方案一，每次一个个扫
 */
void go_line1(void)
{
    Start();
    Tai1_Tai2();
    Tai2_Treasure_Detect();
    if (qr_value == 358 || qr_value == 357) {
        Tai2_Tai3();
        Catch_Treasure3();
        Treasure_Locator3();
        Tai3_door2_Tai5();
        Catch_Treasure3();
        Treasure_Locator3();
        Tai5_Home();
    } else if (qr_value == 367 || qr_value == 368) {
        Tai2_Tai3();
        Catch_Treasure3();
        Treasure_Locator3();
        Tai3_door1_Tai6();
        Tai6_seesaw();
        Tai6_Home();
    } else if (qr_value == 457 || qr_value == 458) {
        Tai2_Tai4();
        Catch_Treasure3();
        Treasure_Locator3();
        Tai4_door4_Tai5();
        Catch_Treasure3();
        Treasure_Locator3();
        Tai5_Home();
    } else if (qr_value == 467 || qr_value == 468) {
        Tai2_Tai4();
        Catch_Treasure3();
        Treasure_Locator3();
        Tai4_door3_Tai6();
        Tai6_seesaw();
        Tai6_Home();
    }
    Front_mid();
    Stop(1000);
    // 第二趟
    Start();
    Tai1_Tai2();
    // Tai2_Treasure_Detect();//还没闪灯
    UP_Tai2_6_noline();
    // down_pt1_6();
    Stop(200);
    LED_Blink();
    if (qr_value == 358 || qr_value == 357) {
        Tai2_Tai3();
        Catch_Treasure3();
        Treasure_Locator3();
        Tai3_door2_Tai5();
        Catch_Treasure3();
        Treasure_Locator3();
        Tai5_Home();
    } else if (qr_value == 367 || qr_value == 368) {
        Tai2_Tai3();
        Catch_Treasure3();
        Treasure_Locator3();
        Tai3_door1_Tai6();
        Tai6_seesaw();
        Tai6_Home();
    } else if (qr_value == 457 || qr_value == 458) {
        Tai2_Tai4();
        Catch_Treasure3();
        Treasure_Locator3();
        Tai4_door4_Tai5();
        Catch_Treasure3();
        Treasure_Locator3();
        Tai5_Home();
    } else if (qr_value == 467 || qr_value == 468) {
        Tai2_Tai4();
        Catch_Treasure3();
        Treasure_Locator3();
        Tai4_door3_Tai6();
        Tai6_seesaw();
        Tai6_Home();
    }
}


/**
 * @brief 方案二，只要扫一次
 */
void go_line2(void)
{
    Start();
    Tai1_Tai2();
    Tai2_Treasure_Detect();
    if (qr_value == 358 || qr_value == 357) {
        Tai2_Tai3();
        Catch_Treasure3();
        Treasure_Locator3();
        Tai3_door2_Tai5();
        if (NOW_Color == 0) {
            Catch_Treasure3();
            Treasure_Locator3();
        } else {
            easy_Catch();
        }

        Tai5_Home();
    } else if (qr_value == 367 || qr_value == 368) {
        Tai2_Tai3();
        Catch_Treasure3();
        Treasure_Locator3();
        Tai3_door1_Tai6();
        Tai6_seesaw_easy();
        Tai6_Home();
    } else if (qr_value == 457 || qr_value == 458) {
        Tai2_Tai4();
        Catch_Treasure3();
        Treasure_Locator3();
        Tai4_door4_Tai5();
        if (NOW_Color == 0) {
            Catch_Treasure3();
            Treasure_Locator3();
        } else {
            easy_Catch();
        }
        Tai5_Home();
    } else if (qr_value == 467 || qr_value == 468) {
        Tai2_Tai4();
        Catch_Treasure3();
        Treasure_Locator3();
        Tai4_door3_Tai6();
        Tai6_seesaw_easy();
        Tai6_Home();
    }

    Stop(1000);
    Front_mid();
    Paw_open();
    Stop(2000);
    // 第二趟
    Start();
    Tai1_Tai2();
    // Tai2_Treasure_Detect();//还没闪灯
    UP_Tai2_6_noline();
    Stop(200);
    LED_Blink();
    if (qr_value == 358 || qr_value == 357) {
        Tai2_Tai3();
       if (NOW_Color == 0) {
            Catch_Treasure3();
            Treasure_Locator3();
        } else {
            easy_Catch();
        }
        Tai3_door2_Tai5();
        if (NOW_Color == 0) {
            Catch_Treasure3();
            Treasure_Locator3();
        } else {
            easy_Catch();
        }
        Tai5_Home();
    } else if (qr_value == 367 || qr_value == 368) {
        Tai2_Tai3();
        if (NOW_Color == 0) {
            Catch_Treasure3();
            Treasure_Locator3();
        } else {
            easy_Catch();
        }
        Tai3_door1_Tai6();
        Tai6_seesaw_easy();
        Tai6_Home();
    } else if (qr_value == 457 || qr_value == 458) {
        Tai2_Tai4();
        if (NOW_Color == 0) {
            Catch_Treasure3();
            Treasure_Locator3();
        } else {
            easy_Catch();
        }
        Tai4_door4_Tai5();
       if (NOW_Color == 0) {
            Catch_Treasure3();
            Treasure_Locator3();
        } else {
            easy_Catch();
        }
        Tai5_Home();
    } else if (qr_value == 467 || qr_value == 468) {
        Tai2_Tai4();
       if (NOW_Color == 0) {
            Catch_Treasure3();
            Treasure_Locator3();
        } else {
            easy_Catch();
        }
        Tai4_door3_Tai6();
        Tai6_seesaw_easy();
        Tai6_Home();
    }
}