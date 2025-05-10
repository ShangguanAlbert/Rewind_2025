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

extern uint32_t t3_i;
extern uint8_t cnt_whiteline;
extern uint8_t qr_flag;
int8_t r;
int8_t g;
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
    Servo_SetAngle(4, 148);//悬空多少
}


/**
 * @brief 前铲抬起
 *
 */
void Front_up(void)
{
    Servo_SetAngle(4, 160);//抬起多少
}


/**
 * @brief 前铲抬高
 *
 */
void Front_up_High(void)
{
    
    Servo_SetAngle(4, 165);//抬起多少
}


/**
 * @brief 张开爪子
 */
void Paw_open(void)
{
   Servo_SetAngle(3, 180); 
}
/**
 * @brief 合上爪子
 */
void Paw_close(void)
{
 Servo_SetAngle(3,130 ); 
}
/**
 * @brief 放下摄像头
 */
void Camera_down(void)
{
 Servo_SetAngle(1, 0); 
}
/**
 * @brief 抬起摄像头
 */
void Camera_up(void)
{
 Servo_SetAngle(1, 63); 
}

/**
 * @brief 抓宝
 */
void Catch(void)
{
    Paw_close();
    Stop(1000);
    Camera_up();
    Paw_open();
}
/**
 * @brief 低速下平台
 */
void down_pt1_6(void)
{
    Front_down();//放下前铲
    Stop(300);
    Reset(100,40);//低速巡线2
    while (hwr != 0) {
        slow_run(40);
    }//红外不扫到前铲就一直走

    Front_mid();//悬空前铲
    Reset(100, 45);
    // stop();
}


/**
 * @brief 上低平台（台3到台6）
 *
 */
void UP_Tai2_6(void)
{
    Front_down();//抬前铲
    while (hwr != 0) {
        slow_run(50);
    }//红外不扫到前铲就一直走

    while (1) {
        slow_run(50);
        if (Huidu_va(5) < white[5] || Huidu_va(6) < white[6]) {
            run(45, 48);
        }
        if (hdxl == 0 || hdxr == 0) {//腰灯扫到红线
            break;
        }
    }
    Front_mid();
    Run_delay(45, 150);
    while (1) {
        run(45,45);
        if (hdxl == 0 || hdxr == 0) {
            break;
        }//左右腰灯扫到第一条黄线开头
    }
    while (1) {
        run(45,45);
        if (hdxl == 1 || hdxr == 1) {
            break;
        }
    }
    // Run_delay(45, 100);
    // while (1) {
    //     slow_run(45);
    //     if (hdxl == 0 || hdxr == 0) {
    //         break;
    //     }
    // }

    Tai1_6_zhuan();
}
/**
 * @brief 上台2
 *
 */
void UP_Tai2(void)
{
    Front_down();
    while (hwr != 0) {
        slow_run(50);
    }

    while (1) {
        slow_run(50);
        if (Huidu_va(5) < white[5] || Huidu_va(6) < white[6]) {
            run(45, 45);
        }
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }
    Front_mid();
    Run_delay(45, 150);
    while (1) {
        slow_run(45);
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
        slow_run(30);
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }
    Tai1_6_zhuan();//低平台转180度
    }//第一条黄线结束时开始转180°
    
    
/**
 * @brief 上台7动作
 *
 */
void UP_Tai7(void)
{
    while (1)
    {
        slow_run(50);//50巡线
        if(hwr==0){//红外扫到，即开始上坡，扫到前铲
            break;
        }
    }
    Reset(300,50);//卡时间巡线
    speed_up(50,105);
    speed_down(105,50);
    Front_down();

    while (1) {
        get_huidu_va();
        if (cnt_whiteline >= 1 && cnt_whiteline < 3) {
            slow_run(50);
        } else if (cnt_whiteline == 0) {
            run(48, 45);
        }
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }
    Run_delay(45, 100);
    while (1) {
        run(48, 45);
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }
    while (1) {
        run(48, 45);
        if (hdxl == 1 || hdxr == 1) {
            break;
        }
    }
    Run_delay(45, 150);
    while (1) {
        run(48, 45);
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
    Reset(200, 50);
    Front_mid();
    while (hwr == 1) {
        slow_run(50);
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
            run(48, 45);
        }
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }
    Run_delay(45, 100);
    while (1) {
        run(48, 45);
        if (hdxl == 0 || hdxr == 0) {
            break;
        }
    }
    while (1) {
        slow_run(45);
        if (hdxl == 1 || hdxr == 1) {
            break;
        }
    }
    Run_delay(45, 300);
    while (1) {
        slow_run(45);
        if (hdxl == 0 || hdxr == 0) {
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
    Reset(800, 40);
    speed_up_high(40, 100);
    speed_down_high(100, 40);
    while (hwr == 1) {
        slow_run(40);
    }
    Front_mid();
}

void Bridge_Travel(void)
{
    while (hwr != 0) {
        slow_run(60);
    }
    Front_down();
    Reset_bridge(700, 65, 1);
    Reset_bridge(150, 90, 1);
    Reset_bridge(200, 120, 1);
    Reset_bridge(140, 80, 1);
    // while (hwr != 0) {
    //     bridge_PD(50, 1);
    // }
    // Front_mid();
    // Reset(300, 60);

    while (hwr != 0) {
        Run(50);
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
        run(speed + 15, 0);
    } else if (Huidu_va(0) > white[0]) {
        run(speed + 15, 10);
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
void Land_Protect_adjust(void)
{
    t3_i = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    while (1) {
        get_huidu_va();
        if (cnt_whiteline != 0) {
            Front_down();
            Reset(200, 60);
            break;
        } else if (cnt_whiteline == 0) {
            // 先向左找，限制2秒
            t3_i = 0; // 重置计时器
            while (1) {
                run(0, 50); // 向左转
                if (Huidu_va(11) > white[11] || Huidu_va(10) > white[10] || Huidu_va(9) > white[9] ||
                    Huidu_va(8) > white[8] ||
                    Huidu_va(7) > white[7]) {
                    Stop(150);
                    break;
                }
                // 如果超过2秒还没找到，跳出循环
                if (t3_i >= 600) { // 假设t3_i的单位是毫秒
                    Stop(150);
                    break;
                }
            }
            // 如果向左没找到，再向右找
            get_huidu_va();
            if (cnt_whiteline == 0) {
                t3_i = 0; // 重置计时器
                while (1) {
                    run(40, -40); // 向右转
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

void Seesaw_with_Adjustion(int time_stop, int time_Seesaw)
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
 * @brief 回程过波浪板
 *
 */
void Back_BLB(void)
{
    while (hdxr != 0) {
        slow_run(45);
    }
    Reset(600, 45);
}

void txs(void){
    while(hwr == 1){
     slow_run(50);
     }
     Front_down();
     HWT101_to_0();
     Reset(600,50);
     while(!outline ){
     Reset(50,50);
     }
    stop();
     Delay_ms(300);
     while(!outline){
     Reset(50,50);
    }
    Front_mid();
     while(!(Huidu_va(10) > white[10] || Huidu_va(11) > white[11])){
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
    //巡线直到扫到黄线
    while (hdxl != 0) {
        slow_run(45);
    }
    //过波浪板
    Reset(1600, 45);
}
/**
 * @brief 获取颜色信息
 *
 */
void Get_Color(void)
{
    while (1)
    {
        if (openmv[2]!=0)
        {
            break;
        }       
    }
    r=0;
    g=0;
    b=0;
    while (r < 3 && g<3 && b<3)
    {
        if (openmv[2]== 1){
            r++;
        }
        else if (openmv[2]== 2)
        {
            g++;
        }
        else if (openmv[2]== 3)
        {
            b++;
        }
        delay_ms(5);   
    } 
    if (r>=3) {
        LCD_SetColor(LCD_RED);
        LCD_FillRect(1, 1, 238, 238);
    } else if (g>=3) {
        LCD_SetColor(LCD_GREEN);
        LCD_FillRect(1, 1, 238, 238);
    } else if (b>=3) {
        LCD_SetColor(LCD_BLUE);
        LCD_FillRect(1, 1, 238, 238);
    } else if (openmv[2] == 0) {
        LCD_SetColor(LCD_WHITE);
        LCD_FillRect(1, 1, 238, 238);
    }
    SHUT_UP();
}
/**
 * @brief 获取二维码信息
 *
 */
void Get_QR(void)
{
    LCD_Clear(); // 清屏，黑色背景
    while (1) {
        QR_Process();  // 处理二维码数据
        if (qr_flag == 1 ) {
            break;
        }
        delay_ms(100); // 延时100ms，避免刷新过快
    }
}

