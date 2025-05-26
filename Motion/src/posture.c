#include "posture.h"
#include "bsp_motor.h"
#include "bsp_SysTick.h"
#include "bsp_servo.h"
#include "bsp_sensor.h"
#include "bsp_adc.h"
#include "reset.h"
#include "trace.h"
#include "turn.h"
#include "basic.h"
#include "bsp_timer.h"
#include "bsp_vision.h"
#include "bsp_lcd.h"
#include "bsp_qr.h"
#include "bsp_compass.h"
#include "bsp_led.h"

extern uint32_t t3_i;
extern uint8_t cnt_whiteline;
extern uint8_t qr_flag;
int8_t Traget_Color;
int8_t NOW_Color;
int8_t Turn_Or_Not;
int8_t r;
int8_t g;
int8_t b;
int8_t tt;
int8_t ss;
int8_t b;

/**
 * @brief 放下前铲
 */
void Front_down(void)
{
    Servo_SetAngle(4, 125); // 放下多少
}

/**
 * @brief 悬空前铲
 */
void Front_mid(void)
{
    Servo_SetAngle(4, 148); // 悬空多少
}

/**
 * @brief 前铲抬起
 *
 */
void Front_up(void)
{
    Servo_SetAngle(4, 160); // 抬起多少
}

/**
 * @brief 前铲抬高
 *
 */
void Front_up_High(void)
{

    Servo_SetAngle(4, 175); // 抬起多少
}

/**
 * @brief 张开爪子
 */
void Paw_open(void)
{
    Servo_SetAngle(3, 180);
}
/**
 * @brief 合上一点点爪子
 */
void Paw_little_close(void)
{
    Servo_SetAngle(3, 160);
}
/**
 * @brief 合上爪子
 */
void Paw_close(void)
{
    Servo_SetAngle(3, 135);
}
/**
 * @brief 放下摄像头
 */
void Camera_down(void)
{
    Servo_SetAngle(1, 0);
}
/**
 * @brief 放下摄像头
 */
void Camera_little_up(void)
{
    Servo_SetAngle(1, 10);
}
/**
 * @brief 放下摄像头
 */
void Camera_down_low(void)
{
    // Servo_SetAngle(1, 0);
    TIM2->CCR1 = 350; // 1ms
}
/**
 * @brief 抬起摄像头
 */
void Camera_up(void)
{
    Servo_SetAngle(1, 63);
}
/**
 * @brief 抬高摄像头
 */
void Camera_up_hight(void)
{
    Servo_SetAngle(1, 75);
}
/**
 * @brief 抓宝
 */
void Catch(void)
{
    Paw_close();
    Stop(3000);
    Camera_up_hight();
    Stop(1000);
    // Paw_open();
    // Stop(800);
}

/**
 * @brief 车子右侧抓宝
 * @paragraph t 后退时间
 */
void Right_Catch(void)
{
    Camera_little_up();
    Stop(300);
    run_delay(-25, -25, 200);
    Stop(300);
    while (1) {
        run(-20, -20);
        if (sebl == 0) {
            break;
        }
    }
    while (1) {
        run(-20, -20);
        if (sebr == 0) {
            break;
        }
    }
    Stop(200);
    // while (1) {
    //     run(-16, -16);
    //     if (sebl == 1) {
    //         break;
    //     }
    // }
    Stop(500);
    Paw_open();
    Stop(500);
    Camera_down();
    Stop(900);
    Catch();
}

/**
 * @brief 车子中间抓宝
 *
 */
void Straight_Catch(void)
{
    Camera_little_up();
    Stop(300);
    run_delay(-25, -25, 200);
    Stop(300);
    while (1) {
        run(-20, -20);
        if (sebl == 0 || sebr == 0) {
            break;
        }
    }
    Stop(500);
    Paw_open();
    Stop(500);
    Camera_down();
    Stop(900);
    Catch();
}

/**
 * @brief 车子左侧抓宝
 * @paragraph t 后退时间
 */
void Left_Catch(void)
{
    Camera_little_up();
    Stop(300);
    run_delay(-25, -25, 200);
    Stop(300);
    while (1) {
        run(-20, -20);
        if (sebr == 0) {
            break;
        }
    }
    while (1) {
        run(-20, -20);
        if (sebl == 0) {
            break;
        }
    }
    Stop(200);
    // while (1) {
    //     run(-16, -16);
    //     if (sebr == 1) {
    //         break;
    //     }
    // }
    Stop(500);
    Paw_open();
    Stop(500);
    Camera_down();
    Stop(900);
    Catch();
}

/**
 * @brief 卡时间后退抓宝
 *
 */
void Catch_Time(int t)
{
    run_delay(-20, -20, t);
    Stop(500);
    Catch();
}

/**
 * @brief 低速下平台
 */
void down_pt1_6(void)
{
    Front_down(); // 放下前铲
    Stop(300);
    Reset(100, 40); // 低速巡线2
    while (hwr != 0) {
        slow_run(40);
    } // 红外不扫到前铲就一直走

    Front_mid(); // 悬空前铲
    Reset(100, 45);
    // stop();
}

/**
 * @brief 上低平台（台3到台6）
 *
 */
void UP_Tai2_6(void)
{
    Front_down(); // 抬前铲
    while (hwr != 0) {
        slow_run(50);
    } // 红外不扫到前铲就一直走

    while (1) {
        slow_run(50);
        if (Huidu_va(5) < white[5] || Huidu_va(6) < white[6]) {
            run(45, 45);
        }
        if (hdxl == 0 || hdxr == 0) { // 腰灯扫到红线
            break;
        }
    }
    Front_mid();        // 悬空前铲
    Run_delay(45, 150); // 卡时间盲走
    while (1) {
        run(45, 45); // 45速度巡线
        if (hdxl == 0 || hdxr == 0) {
            break;
        } // 左右腰灯扫到第一条黄线开头
    }
    while (1) {
        run(45, 45);
        if (hdxl == 1 || hdxr == 1) {
            break;
        } // 左右腰灯知道第一条黄线结束
    }
    Run_delay(45, 150);
    // Run_delay(45, 100);
    while (1) {
        slow_run(45);
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }
    Stop(40);
    Tai1_6_zhuan();
    // Stop (50);
}

/**
 * @brief 上低平台不使用黄线（台3到台6）
 *
 */
void UP_Tai2_6_noline(void)
{
    Front_down(); // 抬前铲
    while (hwr != 0) {
        slow_run(50);
    } // 红外不扫到前铲就一直走
    Front_mid(); // 悬空前铲

    while (1) {
        slow_run(50);
        if (Huidu_va(5) < white[5] || Huidu_va(6) < white[6]) // 扫到红线同时对左右轮速度进行修正（如果需要）
        {
            run(46, 45);
        }
        if (hdxl == 0 || hdxr == 0) { // 腰灯扫到红线
            break;
        }
    }
    Front_mid();            // 悬空前铲
    run_delay(47, 45, 350); // 卡时间盲走
    Stop(40);
    Tai1_6_zhuan();
}

/**
 * @brief 上台2
 *
 */
void UP_Tai2(void)
{
    qr_flag = 0;
    Front_mid();
    while (hwr != 0) {
        slow_run(50);
    }

    while (1) {
        slow_run(50);

        if (Huidu_va(5) < white[5] || Huidu_va(6) < white[6]) {
            run(48, 45);
        }
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }

    Front_mid();
    run_delay(35, 35, 100);
    Front_down();
    Stop(200);
    Start_QR_Detection();
    Check_QR_Status();
    while (1) {
        run(35, 32);

        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }

    // while (1) {
    //     slow_run(45);
    //     if (hdxl == 1 || hdxr == 1) {
    //         break;
    //     }
    // }
    Run_delay(45, 100);
    while (1) {
        run(30, 30);

        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }
    stop();
    Check_QR_Status();
    Check_QR_Again();
    LED_Blink();
    Stop(600);

    // Tai1_6_zhuan(); // 低平台转180度
}

/**
 * @brief 上台7动作
 *
 */
void UP_Tai7(void)
{
    while (1) {
        slow_run(50);   // 50巡线
        if (hwr == 0) { // 红外扫到，即开始上坡，扫到前铲
            break;
        }
    }
    Reset(300, 50); // 卡时间巡线
    speed_up_high(50, 105);
    speed_down_high(105, 50);
    Front_down();

    while (1) {
        get_huidu_va();
        if (cnt_whiteline >= 1 && cnt_whiteline < 3) {
            slow_run(50);
        } else if (cnt_whiteline == 0) {
            run(46, 45);
        }
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }
    Run_delay(45, 100);
    while (1) {
        run(45, 45);
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }
    while (1) {
        run(45, 45);
        if (hdxl == 1 || hdxr == 1) {
            break;
        }
    }
    Run_delay(45, 150);
    while (1) {
        run(45, 45);
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }
    Tai7_zhuan();
}
/**
 * @brief 下台7动作
 *
 */
void Down_Tai7(void)
{
    while (1) {
        get_huidu_va();
        if (cnt_whiteline > 0) {
            break;
        }
        run(45, 45);
    }

    Reset(200, 45);
    Front_mid();
    while (1) {
        slow_run(50);
        if (hwr == 0) {
            break;
        }
    }
}
/**
 * @brief 上台8动作
 *
 */
void UP_Tai8(void)
{
    while (1) {
        slow_run(50);
        if (hwr == 0) {
            break;
        }
    }
    Reset(500, 50);
    speed_up_high(50, 135);
    speed_down_high(135, 50);
    Front_down();

    // speed_up(50,135);
    // speed_down(135,70);
    // Reset(300,70);

    while (1) {
        get_huidu_va();
        if (cnt_whiteline >= 1 && cnt_whiteline < 3) {
            slow_run(50);
        } else if (cnt_whiteline == 0) {
            run(45, 45);
        }
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }
    Run_delay(45, 150);
    while (1) {
        run(45, 50);
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }
    Run_delay(45, 100);
    // while (1) {
    //     slow_run(45);
    //     if (hdxl == 1 || hdxr == 1) {
    //         break;
    //     }
    // }
    // Run_delay(45, 300);
    // while (1) {
    //     slow_run(45);
    //     if (hdxl == 0 || hdxr == 0) {
    //         break;
    //     }
    // }

    Tai8_zhuan();
    // if (hwl==0)
    // {
    //     while (1)
    //     {
    //         run(-25,-25);
    //         if (hwl == 1) {
    //             break;
    //         }
    //     }
    //     run_delay(35,-35,300);

    // }
}
/**
 * @brief 下台8动作
 *
 */
void Down_Tai8(void)
{
    Reset(800, 40);
    speed_up_high(40, 100);
    speed_down_high(100, 40);
    while (hwr == 1) {
        slow_run(40);
    }
    Front_mid();
}
/**
 * @brief 长桥行走
 *
 */
void Bridge_Travel(void)
{
    while (hwr != 0) {
        slow_run(60);
    }
    Front_down();
    Run_delay(60, 800);
    Reset_bridge(750, 65, 1);
    while (hwr != 0) {
        run(50, 50);
    }
    Front_mid();
    Reset(300, 60);
}
/**
 * @brief 长桥行走，去
 *
 */
void Bridge_Travel_go(void)
{
    while (hwr != 0) {
        slow_run(60);
    }
    Front_down();
    run_delay(60,58, 800);
    Reset_bridge(750, 65, 1);
    while (hwr != 0) {
        run(50, 50);
    }
    Front_mid();
    Reset(300, 60);
}

/**
 * @brief 向左飘
 *
 * @param speed 速度
 * @param model 模式
 */
void drift_left(int speed, uint8_t model)
{
    if (Huidu_va(10) > white[10]) {
        run(0, speed + 15);
    } else if (Huidu_va(11) > white[11]) {
        run(10, speed + 15);
    } else if (Huidu_va(8) > white[8]) {
        run(20, speed + 15);
    } else if (Huidu_va(9) > white[9]) {
        run(30, speed + 15);
    } else if (Huidu_va(6) > white[6]) {
        run(30, speed + 15);
    } else {
        if (model == 0)
            slow_run(speed);
        else
            high_run(speed);
    }
}

/**
 * @brief 向右飘
 *
 * @param speed 速度
 * @param model 模式
 */
void drift_right(int speed, uint8_t model)
{
    if (Huidu_va(1) > white[1]) {
        run(speed + 20, 0); // 15
    } else if (Huidu_va(0) > white[0]) {
        run(speed + 20, 10); // 15
    } else if (Huidu_va(3) > white[3]) {
        run(speed + 15, 20);
    } else if (Huidu_va(2) > white[2]) {
        run(speed + 15, 30);
    } else if (Huidu_va(5) > white[5]) {
        run(speed + 15, 30);
    } else {
        if (model == 0) {
            slow_run(speed);
        } else {
            high_run(speed);
        }
    }
}

void drift_right_2(int speed, uint8_t model)
{
    if (Huidu_va(6) > white[6]) {
        run(speed + 15, 30);
    } else if (Huidu_va(5) > white[5]) {
        run(speed + 15, 30);
    } else if (Huidu_va(4) > white[4]) {
        run(speed + 15, 20);
    } else if (Huidu_va(3) > white[3]) {
        run(speed + 15, 10);
    } else if (Huidu_va(2) > white[2]) {
        run(speed + 15, 10);
    } else if (Huidu_va(1) > white[1]) {
        run(speed + 20, 0);
    } else if (Huidu_va(0) > white[0]) {
        run(speed + 20, 0);
    } else {
        if (model == 0) {
            slow_run(speed);
        } else {
            high_run(speed);
        }
    }
}

void Drift_Rightpass_BLB(void)
{
    Front_mid();
    Reset(30, 60);

    while (hdxl != 0) {
        drift_right(60, 0);
    }
    Reset(480, 50);
    // 加速
    Reset(480, 50);
}
/**
 * @brief 上跷跷板修正调整
 *
 * @param time_stop 后半程开始降速时间
 * @param time_Seesaw 总的跷跷板时间
 */
void Past_Seesaw(int time_stop, int time_Seesaw)
{
    // int count_turn = 0;
    t3_i = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    while (1) {
        run(50, 46); // 49
        // Run(65);
        // /*循环修正*/
        // if ((bhwr == 0 && bhwl == 1) || Huidu_va(0) > 80) {
        //     run(40, 70);
        //     delay_ms(5);
        //     count_turn += 3;
        // } else if ((bhwl == 0 && bhwr == 1) || Huidu_va(11) > 80) {
        //     run(70, 40);
        //     delay_ms(5);
        //     count_turn += 3;
        // } else if ((bhwl == 1 && bhwr == 1) || (Huidu_va(0) > 90 && Huidu_va(11) > 90)) {
        //     Run(65);
        // }
        if (t3_i > time_stop) {
            run(30, 28);
            // delay_ms(5);
        }

        if (hwr == 0 && t3_i > time_stop) {
            Front_mid();
            stop();
            break;
        }
        /* 检测到落地点有白线停车 */
        get_huidu_va();
        if (cnt_whiteline > 0 && (t3_i >= time_Seesaw)) {
            stop();
            break;
        }
    }
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    t3_i = 0;
    Stop(1000);
}
/**
 * @brief 跷跷板落地扫不到白线保护程序
 *
 */
void Land_Protect_adjust0(void)
{
    t3_i = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    while (1) {
        get_huidu_va();
        if (cnt_whiteline != 0) {
            // Front_down();
            Reset(200, 60);
            break;
        } else if (cnt_whiteline == 0) {
            // 先向右找，限制2秒
            t3_i = 0; // 重置计时器
            while (1) {
                run(50, 0); // 向右转
                if (Huidu_va(11) > white[11] || Huidu_va(10) > white[10] || Huidu_va(9) > white[9] ||
                    Huidu_va(8) > white[8] ||
                    Huidu_va(7) > white[7]) {
                    Stop(150);
                    break;
                }
                // 如果超过2秒还没找到，跳出循环
                if (t3_i >= 700) { // 假设t3_i的单位是毫秒
                    Stop(150);
                    break;
                }
            }
            // 如果向右没找到，再向左找
            get_huidu_va();
            if (cnt_whiteline == 0) {
                t3_i = 0; // 重置计时器
                while (1) {
                    run(-50, 40); // 向左转
                    if (Huidu_va(1) > white[1] || Huidu_va(2) > white[2] ||
                        Huidu_va(3) > white[3] || Huidu_va(0) > white[0] ||
                        Huidu_va(4) > white[4]) {
                        Stop(150);
                        break;
                    }
                    // 如果超过4秒还没找到，跳出循环
                    if (t3_i >= 1000) { // 假设t3_i的单位是毫秒
                        Stop(150);
                        break;
                    }
                }
            }
            break;
        }
    }
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    t3_i = 0;

    // 根据车头偏向来决定最后的调整方向
    if (Huidu_va(10) > white[10] || Huidu_va(11) > white[11]) {
        // 车头偏右，需要向左调整
        while (1) {
            run(10, 40); // 向左转
            if (Huidu_va(5) > white[5] || Huidu_va(6) > white[6]) {
                break;
            }
        }
    } else if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1]) {
        // 车头偏左，需要向右调整
        while (1) {
            run(40, 10); // 向右转
            if (Huidu_va(5) > white[5] || Huidu_va(6) > white[6]) {
                break;
            }
        }
    }
}
/**
 * @brief 过跷跷板
 *
 */
void Seesaw_with_Adjustion(int time_stop, int time_Seesaw)
{
    int count_turn = 0;
    t3_i           = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    while (1) {
        get_huidu_va();
        Run(60);
        /*循环修正*/
        if (hwr == 1 && hwl == 1) {
            run(40, 55);//run(40, 65);
            Delay_ms(5);
            count_turn += 3;
        } else if (hwr == 1 && hwl == 0) {
            run(60, 40);
            Delay_ms(5);
            count_turn += 3;
        } else if (cnt_whiteline == 0 && hwr == 0) {
            Run(65);
        }
        if (t3_i > time_stop) {
            run(40, 35);
            Delay_ms(5);
        }
        /* 下跷跷板停车 红外检测到 */
        if (hwr != 0 && t3_i > time_stop) {
            Front_mid();
            stop();
            break;
        }
        /* 检测到落地点有白线停车 */
        get_huidu_va();
        if (cnt_whiteline > 0 && (t3_i >= (time_Seesaw + count_turn))) {
            stop();
            break;
        }
    }
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    t3_i = 0;
    Stop(1000);
}
/**
 * @brief 过跷跷板(指南针板)
 *
 */
void Seesaw_with_compass(int time_stop, int time_Seesaw)
{

    HWT101_to_0();
    Stop(40);
    t3_i = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    do {
        Straight_run(0, 50);
    } while (t3_i < time_stop);
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    t3_i = 0;

    t3_i = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    do {
        Straight_run(20, 50);
    } while (t3_i < time_Seesaw);
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    t3_i = 0;
    Stop(1000);
}
/**
 * @brief 在圆圈过跷跷板
 *
 */
void Seesaw_with_Adjustion_Circle(int time_stop, int time_Seesaw)
{
    int count_turn = 0;
    t3_i           = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    while (1) {
        get_huidu_va();
        Run(65);
        /*循环修正*/
        if (hwr == 1 && hwl == 1) {
            run(40, 65);
            Delay_ms(5);
            count_turn += 3;
        } else if (hwr == 1 && hwl == 0) {
            run(65, 40);
            Delay_ms(5);
            count_turn += 3;
        } else if (cnt_whiteline == 0 && hwr == 0) {
            Run(65);
        }
        if (t3_i > time_stop) {
            run(35, 35);
            Delay_ms(5);
        }
        /* 下跷跷板停车 红外检测到 */
        if (hwr != 0 && t3_i > time_stop) {
            Front_mid();
            stop();
            break;
        }
        /* 检测到落地点有白线停车 */
        get_huidu_va();
        if (cnt_whiteline > 0 && (t3_i >= (time_Seesaw + count_turn))) {
            stop();
            break;
        }
    }
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    t3_i = 0;
    Stop(1000);
}
/**
 * @brief 检测到跷跷板并调整姿态到左色标扫到
 *
 */
void Touch_Seesaw_adjust(void)
{
    while (1) {
        drift_left(60, 0);
        if (hwr == 0) break;
    }
    // Front_down();
    Stop(40);
    t3_i = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    // while ((bhwl == 1) || t3_i > 180) {
    //     run(0, 45);
    // }
    while (1) {
        run(-30, 0);
        if (hwl == 0) {
            break;
        } else if (t3_i > 750) { // 没扫到
            while (1) {
                run(-35, 10);
                if (hwl == 0 || t3_i > 1800) break;
            }
            break;
        }
    }
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    t3_i = 0;
    Stop(40);
}
/**
 * @brief 跷跷板落地扫不到白线保护程序
 *
 */
void Land_Protect_adjust(void)
{
    t3_i = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    while (1) {
        get_huidu_va();
        if (cnt_whiteline != 0) {
            Reset_drift_left(60, 0, 100);
            break;
        } else if (cnt_whiteline == 0) {
            while (1) {
                run(0, 50);
                if (Huidu_va(10) > white[10] || Huidu_va(9) > white[9] || Huidu_va(8) > white[8] || Huidu_va(11) > white[11] || Huidu_va(7) > white[7]) break;
            }
            Stop(150);
            break;
        }
    }
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    t3_i = 0;
    while (1) {
        run(0, 40);
        if (Huidu_va(5) > white[5] || Huidu_va(6) > white[6]) {
            break;
        }
    }
}
/**
 * @brief 回程过波浪板，d值加大
 *
 */
void Back_BLB1(void)
{

    t7_i = 0;
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
    do {
        slow_run45();
    } while (t7_i < 2600);
    TIM_ITConfig(TIM7, TIM_IT_Update, DISABLE);
    t7_i = 0;

    // while (hdxr != 0) {
    //     slow_run45();
    // }

    // t7_i = 0;
    // TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
    // do {
    //     slow_run45();
    // } while (t7_i < 700);
    // TIM_ITConfig(TIM7, TIM_IT_Update, DISABLE);
    // t7_i = 0;
}
/**
 * @brief 回程过波浪板
 *
 */
void Back_BLB(void)
{
    while (hdxr != 0) {
        slow_run45();
    }
    Reset(800, 45);
    Reset(800, 45);
}

void txs(void)
{
    while (hwr == 1) {
        slow_run(50);
    }
    Front_down();
    HWT101_to_0();
    Reset(600, 50);
    while (!outline) {
        Reset(50, 50);
    }
    stop();
    Delay_ms(300);
    while (!outline) {
        Reset(50, 50);
    }
    Front_mid();
    while (!(Huidu_va(10) > white[10] || Huidu_va(11) > white[11])) {
        txs_trace();
    }
    //  while(hdxl == 1){
    //  Run_delay(30,10);
    // }
}
/**
 * @brief 出发过波浪板
 *
 */
void Go_BLB(void)
{
    // 巡线直到扫到黄线
    // while (hdxl != 0) {
    //     slow_run45();
    // }
    // // 过波浪板
    Reset(2600, 45);
}
/**
 * @brief 获取目标宝物颜色信息
 *
 */
void Get_Traget_Color(void)
{
    while (1) {
        if (openmv[2] != 0) {
            break;
        }
    }
    r = 0;
    g = 0;
    b = 0;
    while (r < 3 && g < 3 && b < 3) {
        if (openmv[2] == 1) {
            r++;
        } else if (openmv[2] == 2) {
            g++;
        } else if (openmv[2] == 3) {
            b++;
        }
        delay_ms(5);
    }
    if (r >= 3) {
        LCD_SetColor(LCD_RED);
        LCD_FillRect(1, 1, 238, 238);
        Traget_Color = 1;
    } else if (g >= 3) {
        LCD_SetColor(LCD_GREEN);
        LCD_FillRect(1, 1, 238, 238);
        Traget_Color = 2;
    } else if (b >= 3) {
        LCD_SetColor(LCD_BLUE);
        LCD_FillRect(1, 1, 238, 238);
        Traget_Color = 3;
    } else if (openmv[2] == 0) {
        LCD_SetColor(LCD_WHITE);
        LCD_FillRect(1, 1, 238, 238);
    }

    openmv[2] = 0;
    SHUT_UP();
}
/**
 * @brief 获取当前宝物颜色
 *
 */
void Get_Now_Color(void)
{

    r         = 0;
    g         = 0;
    b         = 0;
    NOW_Color = 0;
    t3_i      = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    while (r < 3 && g < 3 && b < 3) {
        if (openmv[2] == 4) {
            r++;
        } else if (openmv[2] == 5) {
            g++;
        } else if (openmv[2] == 6) {
            b++;
        }
        delay_ms(2);
        if (t3_i > 3000) {
            break;
        }
    }
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    t3_i = 0;
    Stop(300);

    if (r >= 3) {
        LCD_SetColor(LCD_MAGENTA); // 玫红色
        LCD_FillRect(1, 1, 238, 238);
        NOW_Color = 4;
    } else if (g >= 3) {
        LCD_SetColor(LCD_YELLOW); // 黄色
        LCD_FillRect(1, 1, 238, 238);
        NOW_Color = 5;
    } else if (b >= 3) {
        LCD_SetColor(LCD_CYAN); // 青色
        LCD_FillRect(1, 1, 238, 238);
        NOW_Color = 6;
    } else if (NOW_Color == 0) {
        LCD_SetColor(LCD_WHITE);
        LCD_FillRect(1, 1, 238, 238);
    }
    stop();
}
/**
 * @brief 获取转弯消息
 *
 */
void Get_Turn(void)
{
    while (1) {
        if (openmv[2] != 0) {
            break;
        }
    }
    tt = 0;
    ss = 0;
    while (tt < 3 && ss < 3) {
        if (openmv[2] == 5) {
            tt++;
        } else if (openmv[2] == 6) {
            ss++;
        }
        delay_ms(5);
    }
    if (tt >= 3) {
        LCD_SetColor(LCD_YELLOW);
        LCD_FillRect(1, 1, 238, 238);
        Turn_Or_Not = 5;

    } else if (ss >= 3) {
        LCD_SetColor(LCD_GREY);
        LCD_FillRect(1, 1, 238, 238);
        Turn_Or_Not = 6;
    }
    openmv[2] = 0;
}
/**
 * @brief 获取二维码信息
 *
 */
void Get_QR(void)
{
    LCD_Clear(); // 清屏，黑色背景

    t3_i = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    while (t3_i < 1500) {
        QR_Process(); // 处理二维码数据
        if (qr_flag == 1) {
            break;
        }
        delay_ms(100); // 延时100ms，避免刷新过快
    }
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    t3_i = 0;

    if (qr_flag == 1) {
        LCD_SetColor(LCD_MAGENTA); // 玫红色
        LCD_FillRect(1, 1, 238, 238);
    }

    if (qr_flag == 0) {
        run_delay(-30, -30, 250);
        stop();

        t3_i = 0;
        TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
        while (t3_i < 1500) {
            QR_Process(); // 处理二维码数据
            if (qr_flag == 1) {
                break;
            }
            delay_ms(100); // 延时100ms，避免刷新过快
        }
        TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
        t3_i = 0;
    }
}
/**
 * @brief 二维码保护程序
 * @return
 */
void Check_QR_Again(void)
{
    if (qr_flag == 0) {
        run_delay(-30, -30, 400);
        stop();

        t3_i = 0;
        TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
        while (1) {
            stop();
            if (qr_flag == 1) {
                LCD_DisplayString(10, 120, "Value:");
                LCD_DisplayNumber(100, 120, qr_value, 10);
            } else {
                LCD_DisplayString(10, 120, "ValueMiss");
            }

            if (qr_flag == 1 || t3_i > 3000) break;
        }
        TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
        t3_i = 0;
        Run_delay(45, 150);
        while (1) {
            run(30, 30);

            if (hdxl == 0 || hdxr == 0) {
                stop();
                break;
            }
        }
    }
}