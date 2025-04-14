
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
    Reset(650,60);//
    // 过桥
    Bridge_Travel();
    // 加速
    Reset(200,60);
    Reset(400,120);
    Reset(200,60);

    UP_Tai2_6();
    //
}

void Tai2_Tai3(void)
{
    down_pt1_6();//下台
    Front_mid();
    Reset(30, 60);
    while (hdxl != 0) {
        drift_right(70, 0);
    }
    Reset(400,70);

    while (hdxl != 0) {
        slow_run(50);
    }
    Reset(1600,50);
    TurnRight_155_Longline();
    Reset(600,60);
    Reset(1200,135);
    Reset(400,70);
    UP_Tai2_6();
    
}

void tai2_tai4(void)
{
    down_pt1_6();//下台
    Front_mid();
    Reset(30, 60);
    while (hdxl != 0) {
        drift_right(70, 0);
    }
    Reset(400,70);

     while (hdxl != 0) {
        slow_run(50);
    }
    Reset(1600,50);
    Reset_drift_left(70,0,500);
    Reset(100,70);
    Reset(1500,130);
    Reset(650,60);
    UP_Tai2_6();
}
