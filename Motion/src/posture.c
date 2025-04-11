#include "posture.h"
#include "bsp_motor.h"
#include "bsp_SysTick.h"
#include "bsp_servo.h"
#include "bsp_sensor.h"
#include "bsp_adc.h"
#include "reset.h"
#include "trace.h"
#include "turn.h"


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
    while (1) {
        slow_run(40);
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }
    while (hwr != 0) {
        slow_run(40);
    }
    Front_mid();
    Reset(60, 45);//
    stop();
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
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }
    while ( hwr!=0) {
        run(45, 45);
    }
    
    Stop(30);
    Front_mid();
    run_delay(40, 40, 200);
    //Tai1_6_zhuan();
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
