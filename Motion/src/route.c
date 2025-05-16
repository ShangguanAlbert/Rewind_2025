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
 * @brief 台1到台2
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
    // 上台2
    // UP_Tai2_6();
    // UP_Tai2();
}
/**
 * @brief 台2识别宝物
 */
void Tai2_Treasure_Detect(void)
{
    UP_Tai2();
    Stop(40);
    Front_down();
    Stop(200);
    Get_QR();
    Tai2_zhuan90_1();
    Camera_down();
    Stop(2000);
    Detect_Color();
    Get_Traget_Color();
    Camera_up();
    run_delay(-25, -25, 200);
    Tai2_zhuan90_2();
}
/**
 * @brief 定位符合颜色的宝物(方案一)
 */
void Treasure_Locator(void)
{
    Camera_down();
    Delay_s(2);
    Locate_target_treasure();
    Get_Turn();
    if (Turn_Or_Not == 6) {
        Run_delay(-20, 380);
        Catch();
    } else {
        Turn_Left25();
        Delay_s(1);
        Get_Turn();
        if (Turn_Or_Not == 6) {
            Run_delay(-20, 480);
            Catch();
            Run_delay(20, 480);
            Turn_Right25();
        } else {
            Turn_Right50();
            Delay_s(1);
            Get_Turn();
            HWT101_to_0();
            if (Turn_Or_Not == 6) {
                Run_delay(-20, 500);
                Catch();
                Run_delay(20, 480);

                Turn_Left22();
            }
        }
    }
    SHUT_UP();

    //    else{
    //       Turn_Right50();
    //    }
    //    Delay_s(1);
    //    if(openmv[2] == 6){
    //     Run_delay(-20,750);
    //     Catch();
    //    }
}
/**
 * @brief 定位符合颜色的宝物(方案二)
 */
void Treasure_Locator2(void)
{
    Camera_down(); // 放下摄像头
    Delay_ms(300);
    Locate_treasure();
    Stop(1000);
    // 识别中间的宝物
    if (openmv[2] == 6) {
        Straight_Catch(); // 抓中间的宝物
    } else if (openmv[2] == 1 || openmv[2] == 2 || openmv[2] == 3) {
        Stop(200);               // 不是目标宝物停200ms
        run_delay(-38, 38, 800); // 向左边转一个大角度
        Stop(600);
        Locate_treasure();
        Stop(800);
        // 开始右转扫描
        while (1) {
            run(35, -35);
            if (openmv[2] == 6) {
                // 扫到后完全停止
                Paw_little_close(); // 收一点爪子
                Stop(800);
                Right_Catch(600); // 抓宝
                break;
                // 如果最左边的也不是先停200ms
            } else if (openmv[2] == 1 || openmv[2] == 2 || openmv[2] == 3) {
                // 停止200ms
                Stop(200);
                Paw_little_close(); // 收一点爪子
                Front_down();       // 放前铲
                Stop(500);
                // 右转直到扫到白线后停止
                while (1) {
                    get_huidu_va();
                    run(35, 0);
                    if (cnt_whiteline > 1) {
                        break;
                    }
                }
                // 抬前铲
                Front_up();
                Stop(200);
                // 向右边转一个大角度
                run_delay(32, -38, 800);
                Stop(500);
                // 向左边回转直到扫到宝物
                while (1) {
                    run(-35, 35);
                    if (openmv[2] == 6) {
                        // 完全停止
                        Paw_little_close();
                        Stop(800);
                        Left_Catch(500); // 抓宝
                        break;
                    }
                }
                break;
            }
        }
    }
}

/**
 * @brief 定位符合颜色的宝物(方案三)——同时扫三个宝物
 */
void Treasure_Locator3(void)
{
    Camera_down();
    Delay_ms(300);
    Straight_back();
    Locate_treasure();
    if (NOW_Color == 5) {
        Paw_little_close();
        Straight_Catch();
        down_pt1_6();
    } else if (NOW_Color == 4) {
        run_delay(-35, 35, 700); // 向左边转一个大角度
        Stop(800);
        // 开始右转扫描
        while (1) {
            run(30, -30);
            if (openmv[2] == 6) {
                // 扫到后完全停止
                Stop(800);
                Right_Catch(600); // 抓宝
                break;
            }
        }
        run_delay(35, 0, 700);
        down_pt1_6();
    } else if (NOW_Color == 6) {
        run_delay(35, -35, 700); // 向右边转一个大角度
        Stop(600);
        Locate_treasure();
        Stop(800);
        // 开始右转扫描
        while (1) {
            run(-32, 32);
            if (openmv[2] == 6) {
                // 扫到后完全停止
                Stop(800);
                Left_Catch(500); // 抓宝
                break;
            }
        }
        run_delay(0, 35, 700);
        down_pt1_6();
    }
}

/**
 * @brief 抓宝方案四，先下台在后退上台确保转正
 *
 */
void Treasure_Locator4(void)
{
    Front_down();
    Stop(200);
    while (1) {
        get_huidu_va();
        slow_run(20);
        if (cnt_whiteline > 0) {
            break;
        }
    }
    slow_run1(35);
    HWT101_to_0();
}

/**
 * @brief 上台定位
 *
 */
void Catch_Treasure(void)
{
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
/**
 * @brief 方案一同时扫三个宝物（斜坡上就放摄像头）
 *
 */
void Catch_Treasure2(void)
{
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
    HWT101_to_0();
    Stop(200);
    Deg_IN();
    t3_i = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    while (t3_i < 800) {
        Straight_run_back(45);
        if (hwr == 0) {
            run_delay(-45, -45, 200);
            break;
        }
    }
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    t3_i = 0;
    Stop(300);
    Front_up();
    Camera_down_low();
    Stop(300);
    Locate_target_treasure();
    Get_Now_Color();
    if (NOW_Color == 0) {
        run_delay(-35, -35, 100);
        stop();
    }
    Get_Now_Color();
    SHUT_UP();
}

/**
 * @brief 方案3抓宝（退到腰灯扫到红线）
 *
 */
void Catch_Treasure3(void)
{
    UP_Tai2_6_noline();
    Stop(250);
    Front_down();
    Stop(200);
    while (1) {
        slow_run(45);
        if (hwr == 0) break;
    }
    Reset(300, 45);
    Stop(250);
    HWT101_to_0();
    Stop(250);
    Deg_IN();
    // t3_i = 0;
    // TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    // while (t3_i < 800) {
    while (1) {
        Straight_run_back(45);
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }
    // TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    // t3_i = 0;
    Stop(300);
    Front_up();
    Camera_down_low();
    Stop(400);
    Locate_target_treasure();
    Get_Now_Color();
    if (NOW_Color == 0) {
        run_delay(-35, -35, 100);
        stop();
    }
    Get_Now_Color();
    SHUT_UP();
}

/**
 * @brief 台2到台3
 */
void Tai2_Tai3(void)
{
    down_pt1_6(); // 下台
    Reset(60, 60);
    // 向右漂移直到左腰灯测到白线
    while (hdxl != 0) {
        drift_right(70, 0);
    }
    // 修正
    Reset(320, 60);
    // 过波浪板
    Go_BLB();
    // 右转135度
    TurnRight_135_Longline();
    Stop(300);
    // 修正
    Reset(500, 70);
    // 加速
    speed_up(70, 170);
    Reset(250, 170);
    speed_down(170, 50);
    // 上台3
    // UP_Tai2_6();
}
/**
 * @brief 台到台2
 */
void Tai2_Tai4(void)
{
    down_pt1_6(); // 下台
    // 修正
    Reset(60, 60);
    // 向右漂移直到左腰灯扫到白线
    while (hdxl != 0) {
        drift_right(70, 0);
    }
    // 巡线
    Reset(320, 60);
    // 过波浪板
    Go_BLB();
    // 向左漂移
    Reset_drift_left(70, 0, 800);
    // 修正
    Reset(250, 70);
    // 加速
    speed_up(70, 190);
    Reset(150, 190);
    speed_down(190, 50);
    // 上台4
    // UP_Tai2_6();
}

/**
 * @brief 下台3经过门2到台5
 */
void Tai3_door2_Tai5(void)
{
    // 下台3
    down_pt1_6();
    // 修正
    Reset(100, 70);
    // 加速
    speed_up(70, 160);
    speed_down(160, 70);
    // 低速巡线直到右灰度灯扫到白线
    while (1) {
        slow_run(70);
        if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1]) {
            break;
        }
    }
    // 向右漂移，过弯
    Reset_drift_right(70, 0, 700);
    // 修正

    Reset(500, 50);
    // speed_up(50, 85);
    // speed_down(85, 50);
    while (hdxl != 0 || hdxr != 0) {
        slow_run(50);
    }
    Reset(800, 50);
    speed_up(50, 120);
    Reset(500, 120);
    speed_down(120, 50);
    stop();

    // while (1) {
    //     slow_run(70);
    //     if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1]) {
    //         break;
    //     }
    // }
    // // 向左漂移一段时间，过弯
    // Reset_drift_left(70, 0, 500);
    // // 修正
    // Reset(250, 70);
    // // 加速
    // speed_up(70, 150);
    // speed_down(150, 50);
    // // 上台5
    // // UP_Tai2_6();
}

/**
 * @brief 台3到台6
 *
 */
void Tai3_door1_Tai6(void)
{
    Reset(100, 70);
    // 加速
    speed_up(70, 160);
    speed_down(160, 70);
    TurnRight_90_Ldetect_3_indoor1();
    Reset(250, 50);
    speed_up(50, 95);
    speed_down(95, 50);
    while (hdxl != 0 || hdxr != 0) {
        slow_run(50);
    }
    Reset(1000, 50);
}

/**
 * @brief 台4经过门4到台5
 */
void Tai4_door4_Tai5(void)
{
    // 下台4
    // down_pt1_6();
    // 修正
    Reset(100, 70);
    // 加速
    speed_up(70, 170);
    speed_down(170, 70);
    // 左转90度，左灰度灯判断转弯条件
    TurnLeft_90_Ldetect_4();
    Reset(250, 50);
    speed_up(50, 95);
    speed_down(95, 50);
    while (hdxl != 0 || hdxr != 0) {
        slow_run(50);
    }
    Reset(1000, 50);
    // 左转90度，左灰度灯判断转弯条件
    TurnLeft_90_Ldetect_5();
    Stop(200);
    // 修正
    Reset(350, 70);
    // 加速
    speed_up(70, 160);
    speed_down(160, 70);
    // 上台5
    // UP_Tai2_6();
}
/**
 * @brief 台5到台7
 */
void Tai5_Tai7(void)
{
    // 下台
    // down_pt1_6();
    // 修正
    Reset(200, 50);
    // 加速
    speed_up(50, 190);
    Reset(200, 190);
    speed_down(190, 50);
    // T形山前，左转90度
    TurnLeft_90_Ldetect_Mountain();
    Stop(40);
    // 走梯形山后无白线直走
    txs();
    // 左转
    Out_T_TurnLeft_90_Ldetect();
    Stop(40);
    // 巡线
    Reset(250, 60);
    // 加速
    speed_up(60, 185);
    speed_down(185, 50);
    // 上台7
    UP_Tai7();
}
/**
 * @brief 台5到台8
 */
void Tai5_Tai8(void)
{
    // 下台5
    // down_pt1_6();
    // 修正
    Reset(200, 50);
    // 加速
    speed_up(50, 190);
    Reset(200, 190);
    speed_down(190, 50);
    // 左转90度
    TurnLeft_90_Ldetect_Mountain();
    Stop(40);
    // 上梯形山后无白线直走
    txs();
    // 右转
    Out_T_TurnRight_90_Ldetect();
    Stop(40);
    // 巡线
    Reset(250, 70);
    // 加速
    speed_up(70, 140);
    // 减速
    speed_down(140, 50);
    // 上台八
    UP_Tai8();
}
/**
 * @brief 从台7回家
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
    // 右飘进波浪板
    while (hdxr != 0) {
        drift_right(50, 0);
    }
    // 修正
    Reset(500, 45);
    // 走波浪板
    Back_BLB();
    // 右转135度进长桥
    TurnRight_135_Longline();
    Stop(50);
    // 修正
    Reset(250, 50);
    // 加速
    speed_up(50, 100);
    speed_down(100, 50);
    // 走长桥
    Bridge_Travel();
    // 修正
    Reset(600, 60);
    // 上台
    UP_Tai2_6();
}

/**
 * @brief 从台8回家
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
    Reset(1200, 45);
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
/**
 * @brief 走台6跷跷板圆圈
 *
 */
void Tai6_seesaw(void)
{
    TurnRight_135_Circle();
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
    Stop(40);
    Catch_Treasure3();
    Treasure_Locator3();
    // UP_Tai2_6_noline();
    // down_pt1_6();
    TurnLeft_90_Rdetect_4();
    Stop(50);
    Touch_Seesaw_adjust();
    Seesaw_with_Adjustion(1200, 2100);
    Land_Protect_adjust();
    while (1) {
        drift_left(60, 0);
        if (hdxr == 0) {
            break;
        }
    }
    while (1) {
        drift_right(60, 0);
        if (hdxl == 0) {
            break;
        }
    }
    while (1) {
        run(-30, 30);
        if (Huidu_va(5) > white[5] || Huidu_va(6) > white[6]) {
            break;
        }
    }
    Stop(40);
    Reset(110, 60);
}

/**
 * @brief 台六出翘翘板去台七
 *
 */
// void Tai6_Tai7(void){

// }