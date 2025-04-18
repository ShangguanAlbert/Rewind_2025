
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
    // down_pt1_6();
    // // 矫正
    // Reset(650,60);//
    // // 过桥
    // Bridge_Travel();
    // // // 加速
    // speed_up(60,135);
    // speed_down(135,60);

    UP_Tai2_6();
    // //
}

void Tai2_Tai3(void)
{
    down_pt1_6();//下台
    Reset(30, 60);
    while (hdxl != 0) {
        drift_right(70, 0);
    }
    Reset(400,70);

    while (hdxl != 0) {
        slow_run(50);
    }
    Reset(1600,50);
    TurnRight_135_Longline();
    Reset(600,60);
    Reset(1200,135);
    Reset(400,70);
    UP_Tai2_6();
    
}

void Tai2_Tai4(void)
{
    down_pt1_6();//下台
    Reset(60, 60);
    while (hdxl != 0) {
        drift_right(70, 0);
    }
    Reset(320,70);

     while (hdxl != 0) {
        slow_run(50);
    }
    Reset(1600,45);
    Reset_drift_left(70,0,800);
    Reset(250,70);
    speed_up(70,190);
    // Reset(200,190);
    speed_down(190,50);
    //UP_Tai2_6();
}
void Tai3_Tai5(void)
{
    down_pt1_6();
    Reset(200,70);
    Reset(800,120);
    Reset(200,70);
    Reset_drift_right(70,0,500);
    



}

/*
下台3从门2通过
*/
void Tai3_door2_Tai5(void)
{
    down_pt1_6();
    Reset(200,70);
    Reset(1000,120);
    Reset(400,70);
    Reset_drift_right(70,0,500);
    Reset(300,70);
    Reset(1300,120);
    Reset(200,70);
    Reset_drift_left(70,0,500);
    Reset(400,70);
    Reset(800,120);
    Reset(250,70);
    UP_Tai2_6();
}



/*
下台三右转进门1
*/
void Tai3_door1_Tai5(void)
{
    down_pt1_6();
    Reset(200,70);
    Reset(1000,120);
    Reset(300,70);
    //右转90度
    TurnRight_90_Rdetect_in();
    Stop(50);
    Reset(200,50);
    Reset(200,70);
    Reset(850,115);
    Reset(300,70);
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

}


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
