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

extern uint32_t t3_i;
extern uint8_t cnt_whiteline;

/**
 * @brief 放下前铲
 */
void Front_down(void)
{
    Servo_SetAngle(4,125);//放下多少
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

void down_Tai7();
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
         slow_run(50);
        if (Huidu_va(5)<white[5]||Huidu_va(6)<white[6])
        {
            run(48, 45);
        }
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }
    Front_mid();
    Run_delay(45,100);
    while (1)
    {
        slow_run(45);
        if(hdxl==0 ||hdxr==0){
            break;
        }
    }
    while (1)
    {
        slow_run(45);
        if(hdxl==1 ||hdxr==1){
            break;
        }
    }
    Run_delay(45,100);
    while (1)
    {
        slow_run(45);
        if(hdxl==0 ||hdxr==0){
            break;
        }
    }
    
    Tai1_6_zhuan();
    
}
/**
 * @brief 上台7动作
 *
 */
void UP_Tai7(void)
{
    while (1)
    {
        slow_run(50);
        if(hwr==0){
            break;
        }
    }
    Reset(300,50);
    speed_up(50,105);
    speed_down(105,50);
    Front_down();
    while (1) {
        slow_run(50);
    //    if (Huidu_va(5)<white[5]||Huidu_va(6)<white[6])
    //    {
    //        run(48, 45);
    //    }
       if (hdxl == 0 || hdxr == 0) {
           break;
       }
   }
   Front_down();

   Run_delay(45,100);
   while (1)
   {
       Run(45);
       if(hdxl==0 ||hdxr==0){
           break;
       }
   }
   while (1)
   {
       Run(45);
       if(hdxl==1 ||hdxr==1){
           break;
       }
   }
   Run_delay(45,50);
   while (1)
   {
       Run(35);
       if(hdxl==0 ||hdxr==0){
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
   Reset(200, 50);
   while (hwr == 1) {
       slow_run(50);
   }
   Front_mid();
}
/**
 * @brief 上台8动作
 *
 */
void UP_Tai8(void)
{
    while (1)
    {
        slow_run(50);
        if(hwr==0){
            break;
        }
    }
    Reset(500,50);
    speed_up_high(50,135);
    speed_down_high(135,50);
    

    // speed_up(50,135);
    // speed_down(135,70);
    // Reset(300,70);

    while (1) {
        slow_run(50);
       if (Huidu_va(5)<white[5]||Huidu_va(6)<white[6])
       {
           run(48, 45);
       }
       if (hdxl == 0 || hdxr == 0) {
           break;
       }
   }
   Front_mid();
   Run_delay(45,100);
   while (1)
   {
       slow_run(45);
       if(hdxl==0 ||hdxr==0){
           break;
       }
   }
   while (1)
   {
       slow_run(45);
       if(hdxl==1 ||hdxr==1){
           break;
       }
   }
   Run_delay(45,100);
   while (1)
   {
       slow_run(45);
       if(hdxl==0 ||hdxr==0){
           break;
       }
   }
   
   Tai8_zhuan();
}
/**
 * @brief 下台8动作
 *
 */
void Down_Tai8(void)
 {
    Reset(800,40);
    speed_up_high(40,100);
    speed_down_high(100,40);
    while (hwr == 1) {
        slow_run(40);
    }
    Front_mid();
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

void drift_right_2(int speed, uint8_t model)
 {
     if (Huidu_va(6) > white[6]) {
         run(speed + 15, 30);
     } else if (Huidu_va(5) > white[5]) {
         run(speed + 15, 30);
     } else if (Huidu_va(4) > white[4]) {
         run(speed + 15, 20);
     } else if (Huidu_va(3) >white [3]) {
         run(speed + 15, 10);
     } else if (Huidu_va(2) > white[2]) {
         run(speed + 15, 10);
     } else if (Huidu_va(1) > white[1]) {
         run(speed + 15, 0);
     } else if (Huidu_va(0) > white[0]) {
         run(speed + 15, 0);
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
/**
 * @brief 上跷跷板修正调整
 *
 * @param time_stop 后半程开始降速时间
 * @param time_Seesaw 总的跷跷板时间
 */
void Past_Seesaw(int time_stop, int time_Seesaw)
{
    // int count_turn = 0;
    t3_i           = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    while (1) {
        run(50,46);//49
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
        if (cnt_whiteline > 0 && (t3_i >= time_Seesaw )) {
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
void Land_Protect_adjust(void)
{
    t3_i = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    while (1) {
        get_huidu_va();
        if (cnt_whiteline != 0) {
            Front_down();
            Reset(200,60);
            break;
        } else if (cnt_whiteline == 0) {
            // 先向左找，限制2秒
            t3_i = 0;  // 重置计时器
            while (1) {
                run(0, 50);  // 向左转
                if (Huidu_va(11) > white[11]||Huidu_va(10) > white[10] || Huidu_va(9) > white[9] || 
                    Huidu_va(8) > white[8] || 
                    Huidu_va(7) > white[7]) {
                    Stop(150);
                    break;
                }
                // 如果超过2秒还没找到，跳出循环
                if (t3_i >= 600) {  // 假设t3_i的单位是毫秒
                    Stop(150);
                    break;
                }
            }
            // 如果向左没找到，再向右找
            get_huidu_va();
            if (cnt_whiteline == 0) {
                t3_i = 0;  // 重置计时器
                while (1) {
                    run(40,-40 );  // 向右转
                    if (Huidu_va(1) > white[1] || Huidu_va(2) > white[2] || 
                        Huidu_va(3) > white[3] || Huidu_va(0) > white[0] || 
                        Huidu_va(4) > white[4]) {
                        Stop(150);
                        break;
                    }
                    // 如果超过4秒还没找到，跳出循环
                    if (t3_i >= 1000) {  // 假设t3_i的单位是毫秒
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
            run(10, 40);  // 向左转
            if (Huidu_va(5) > white[5] || Huidu_va(6) > white[6]) {
                break;
            }
        }
    } else if (Huidu_va(0) > white[0] || Huidu_va(1) > white[1]) {
        // 车头偏左，需要向右调整
        while (1) {
            run(40, 10);  // 向右转
            if (Huidu_va(5) > white[5] || Huidu_va(6) > white[6]) {
                break;
            }
        }
    }
}
