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


/**
 * @brief 放下前铲
 */
void Front_down(void)
{
    Servo_SetAngle(4,135);//放下多少
}
/**
 * @brief 悬空前铲
 */
void Front_mid(void)
{
    Servo_SetAngle(4, 148);//?
}
/**
 * @brief 前铲抬起
 *
 */
void Front_up(void)
{
    Servo_SetAngle(4, 160);
}
/**
 * @brief 前铲抬高
 *
 */
void Front_up_High(void)
{
    
    Servo_SetAngle(4, 165);
}

/**
 * @brief 低速下平台
 */
void down_pt1_6(void)
{
    Front_down();
    Stop(300);
    Reset(100,40);
    while (hwr != 0) {
        slow_run(40);
    }
    Front_mid();
    Reset(100, 45);//
    // stop();
}

/**
 * @brief 上台2到台6动作
 *
 */
void UP_Tai2_6(void)
{
    Front_down();
    while (hwr != 0) {
        slow_run(50);
    }


    while (1) {
         slow_run(55);
        if (Huidu_va(5)<white[5]||Huidu_va(6)<white[6])
        {
            run(48, 45);
        }
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
        
    }

    
    Stop(30);
    Front_mid();
    run_delay(50, 50, 350);
    Tai1_6_zhuan();
    
}

void Bridge_Travel(void)
{
    while (hwr !=0) {
            slow_run(60);
        }
    Front_down();
    Reset_bridge(700, 65, 1);
    Reset_bridge(150,90,1);
    Reset_bridge(200,120,1);
    Reset_bridge(140,80,1);
    while(hwr!=0){
        bridge_PD(50, 1);
    }
    Front_mid();
    Reset(200,60);
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
        run(speed + 15, 0);
    } else if (Huidu_va(0) > white[0]) {
        run(speed + 15, 10);
    } else if (Huidu_va(3) >white [3]) {
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
void Drift_Rightpass_BLB(void)
{
    Front_mid();
    Reset(30, 60);
    
    while (hdxl != 0) {
        drift_right(60, 0);
    }
    Reset(480,50);
    //加速
    Reset(480,50);
    
}
