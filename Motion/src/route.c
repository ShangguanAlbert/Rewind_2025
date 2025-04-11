
#include "route.h"
#include "reset.h"
#include "posture.h"
#include "trace.h"
#include "bsp_adc.h"
#include "bsp_servo.h"
#include "bsp_sensor.h"
#include "bsp_SysTick.h"



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
}