#include "trace.h"
#include "bsp_compass.h"
#include "pid_turn.h"
#include "bsp_sensor.h"
#include "bsp_servo.h"
#include "posture.h"

int Gray_sum;
int speed;
int lastError;
int motorSpeed;
int lastm1Speed; // 上次速度
int lastm2Speed;
int mSpeed_right;
int mSpeed_left;
uint8_t cnt_whiteline;
float sum = 0.0;
float error;
float KP;
float KD;
extern float JD;

int32_t thr_whiteline[] = thr_line;  // 判线阈值
int32_t white[]         = thr_white; // 白线阈值
int32_t green[]         = thr_green; // 绿地阈值
/**
 * @brief 获取灰度信息
 */
void get_huidu_va(void)
{
    uint8_t i;
    Gray_sum      = 0;
    sum           = 0.0;
    cnt_whiteline = 0;
    for (i = 0; i < 12; i++) {
        sum += Filter(i);
        if (Filter(i) > thr_whiteline[i]) {
            cnt_whiteline++;
        }
    }
}
/**
 * @brief 巡线函数
 */
void Trace(void)
{
    if (Huidu_va(1) > white[1] && Huidu_va(2) > white[2] && Huidu_va(3) > white[3] &&
        Huidu_va(4) > white[4] && Huidu_va(5) > white[5] && Huidu_va(6) > white[6] &&
        Huidu_va(7) > white[7] && Huidu_va(8) > white[8] && Huidu_va(9) > white[9] &&
        Huidu_va(10) > white[10]) {
        error = 0; // 在全白地面行驶
    } else if (Huidu_va(1) < green[1] && Huidu_va(2) < green[2] && Huidu_va(3) < green[3] &&
               Huidu_va(4) < green[4] && Huidu_va(5) < green[5] && Huidu_va(6) < green[6] &&
               Huidu_va(7) < green[7] && Huidu_va(8) < green[8] && Huidu_va(9) < green[9] &&
               Huidu_va(10) < green[10]) {
        error = 0; // 在绿地上
    } else if (Huidu_va(5) > white[5] && Huidu_va(6) > white[6]) {
        error = 0; // 白线位于灰度灯5,6之间
    } else if ((Huidu_va(5) > white[5] || Huidu_va(6) > white[6]) &&
               (Huidu_va(0) > white[0] || Huidu_va(1) > white[1])) {
        error = 0; // 中间的灰度灯和右边的灰度灯同时位于白线上（干扰线）
    } else if ((Huidu_va(5) > white[5] || Huidu_va(6) > white[6]) &&
               (Huidu_va(11) > white[11] || Huidu_va(10) > white[10])) {
        error = 0; // 中间的灰度灯和左边的灰度灯同时位于白线上（干扰线）
    } else if (cnt_whiteline >= 3 || (cnt_whiteline >= 2 && (Huidu_va(5) > white[5] || Huidu_va(6) > white[6]))) {
        error = 0; // 有三个灰度灯扫到白线 或者 5，6灰度灯扫到白线的同时总白线数大于等于2
    } else {
        Gray_sum = Huidu_va(0) * (3) +
                   Huidu_va(1) * (5) + Huidu_va(2) * (4) + Huidu_va(3) * (3) + Huidu_va(4) * (2) +
                   Huidu_va(5) * (1) + Huidu_va(6) * (-1) +
                   Huidu_va(7) * (-2) + Huidu_va(8) * (-3) + Huidu_va(9) * (-4) + Huidu_va(10) * (-5) +
                   Huidu_va(11) * (-3);                // 灰度值加权和
        error = Gray_sum * 1.0 * (3000.0 / sum * 1.0); // 误差
    }

    motorSpeed   = KP * error + KD * (error - lastError); // 修正值
    lastError    = error;                                 // 将这一次的偏差记为上一次的偏差
    mSpeed_right = speed - motorSpeed;                    // 右轮速度
    mSpeed_left  = speed + motorSpeed;                    // 左轮速度
    lastm1Speed  = mSpeed_right;                          // 记录右轮速度
    lastm2Speed  = mSpeed_left;                           // 记录左轮速度
    // 限幅
    if (speed <= 125) {
        if (mSpeed_right < 0) {
            mSpeed_right = 0;
        } else if (mSpeed_right > (1.6 * speed)) {
            mSpeed_right = 1.6 * speed;
        }

        if (mSpeed_left < 0) {
            mSpeed_left = 0;
        } else if (mSpeed_left > 1.6 * speed) {
            mSpeed_left = 1.6 * speed;
        }
    }

    if (speed > 125 && speed <= 160) {
        if (mSpeed_right < 0) {
            mSpeed_right = 0;
        } else if (mSpeed_right > (1.35 * speed)) {
            mSpeed_right = 1.35 * speed;
        }

        if (mSpeed_left < 0) {
            mSpeed_left = 0;
        } else if (mSpeed_left > (1.35 * speed)) {
            mSpeed_left = 1.35 * speed;
        }
    }
    if (speed > 160) {
        if (mSpeed_right < 0) {
            mSpeed_right = 0;
        } else if (mSpeed_right > (1.35 * speed)) {
            mSpeed_right = 1.35 * speed;
        }

        if (mSpeed_left < 0) {
            mSpeed_left = 0;
        } else if (mSpeed_left > (1.35 * speed)) {
            mSpeed_left = 1.35 * speed;
        }
    }

    set_pwm(1, mSpeed_right, speed);
    set_pwm(2, mSpeed_left, speed);
}
/**
 * @brief 巡线函数，限速
 */
void Trace_transVelocity(void)
{
    if (Huidu_va(1) > white[1] && Huidu_va(2) > white[2] && Huidu_va(3) > white[3] &&
        Huidu_va(4) > white[4] && Huidu_va(5) > white[5] && Huidu_va(6) > white[6] &&
        Huidu_va(7) > white[7] && Huidu_va(8) > white[8] && Huidu_va(9) > white[9] &&
        Huidu_va(10) > white[10]) {
        error = 0;
    } else if (Huidu_va(1) < green[1] && Huidu_va(2) < green[2] && Huidu_va(3) < green[3] &&
               Huidu_va(4) < green[4] && Huidu_va(5) < green[5] && Huidu_va(6) < green[6] &&
               Huidu_va(7) < green[7] && Huidu_va(8) < green[8] && Huidu_va(9) < green[9] &&
               Huidu_va(10) < green[10]) {
        error = 0;
    } else if (Huidu_va(5) > white[5] && Huidu_va(6) > white[6]) {
        error = 0;
    } else if ((Huidu_va(5) > white[5] || Huidu_va(6) > white[6]) &&
               (Huidu_va(0) > white[0] || Huidu_va(1) > white[1])) {
        error = 0;
    } else if ((Huidu_va(5) > white[5] || Huidu_va(6) > white[6]) &&
               (Huidu_va(11) > white[11] || Huidu_va(10) > white[10])) {
        error = 0;
    } else if (cnt_whiteline >= 3 || (cnt_whiteline >= 2 && (Huidu_va(5) > white[5] || Huidu_va(6) > white[6]))) {
        error = 0;
    } else {
        Gray_sum = Huidu_va(0) * (3) +
                   Huidu_va(1) * (5) + Huidu_va(2) * (4) + Huidu_va(3) * (3) + Huidu_va(4) * (2) +
                   Huidu_va(5) * (1) + Huidu_va(6) * (-1) +
                   Huidu_va(7) * (-2) + Huidu_va(8) * (-3) + Huidu_va(9) * (-4) + Huidu_va(10) * (-5) +
                   Huidu_va(11) * (-3);
        error = Gray_sum * 1.0 * (3000.0 / sum * 1.0);
    }

    motorSpeed = KP * error + KD * (error - lastError);
    // 限制轮速调节值
    if (motorSpeed > 20) {
        motorSpeed = 20; // 20
    }
    if (motorSpeed < -20) {
        motorSpeed = -20;
    }

    lastError    = error;
    mSpeed_right = speed - motorSpeed; // 右轮速度
    mSpeed_left  = speed + motorSpeed; // 左轮速度
    lastm1Speed  = mSpeed_right;
    lastm2Speed  = mSpeed_left;
    // 限幅
    if (speed <= 125) {
        if (mSpeed_right < 0) {
            mSpeed_right = 0;
        } else if (mSpeed_right > (1.6 * speed)) {
            mSpeed_right = 1.6 * speed;
        }

        if (mSpeed_left < 0) {
            mSpeed_left = 0;
        } else if (mSpeed_left > 1.6 * speed) {
            mSpeed_left = 1.6 * speed;
        }
    }

    if (speed > 125 && speed <= 160) {
        if (mSpeed_right < 0) {
            mSpeed_right = 0;
        } else if (mSpeed_right > (1.35 * speed)) {
            mSpeed_right = 1.35 * speed;
        }

        if (mSpeed_left < 0) {
            mSpeed_left = 0;
        } else if (mSpeed_left > (1.35 * speed)) {
            mSpeed_left = 1.35 * speed;
        }
    }
    if (speed > 160) {
        if (mSpeed_right < 0) {
            mSpeed_right = 0;
        } else if (mSpeed_right > (1.35 * speed)) {
            mSpeed_right = 1.35 * speed;
        }

        if (mSpeed_left < 0) {
            mSpeed_left = 0;
        } else if (mSpeed_left > (1.35 * speed)) {
            mSpeed_left = 1.35 * speed;
        }
    }

    set_pwm(1, mSpeed_right, speed);
    set_pwm(2, mSpeed_left, speed);
}

/**
 * @brief 低速巡线
 * @param N 设定的速度
 */
void slow_run(int N)
{
    get_huidu_va();
    speed = N;
    if (speed < 50) {
        KP = 0.0077;
        KD = 0.15;
    } else if (speed >= 50 && speed < 60) { // 50
        KP = 0.0070;
        KD = 0.1;
    } else if (speed >= 60 && speed < 70) { // 60
        KP = 0.0045;
        KD = 0.005;
    } else if (speed >= 70 && speed < 80) { // 70
        KP = 0.00400;
        KD = 0.00558;
    } else if (speed >= 80 && speed < 90) { // 80
        KP = 0.0041;
        KD = 0.005;
    } else { // 90
        KP = 0.00413;
        KD = 0.17;
    }
    Trace();
}
/**
 * @brief 低速巡线
 * @param N 设定的速度
 */
void slow_run1(int N)
{
    get_huidu_va();
    speed = N;
    KP    = 0.01;
    KD    = 0.2;
    Trace();
}
/**
 * @brief 高速巡线
 * @param N 设定的速度
 */
void high_run(int N)
{
    get_huidu_va();
    speed = N;
    if (speed > 90 && speed < 100) {
        KP = 0.001982; // p大会抽会扭 0.00413
        KD = 0.17;     // d小回到白线的速度就慢 0.005565 72
    } else if (speed >= 100 && speed < 110) {
        KP = 0.00199; // 0.001982
        KD = 0.18;    // 0.02899
    } else if (speed >= 110 && speed < 120) {
        KP = 0.001985;
        KD = 0.017; // 0.0265
    } else if (speed >= 120 && speed < 130) {
        KP = 0.0022; // 0.00198
        KD = 0.18;   // 0.02644
    } else if (speed >= 130 && speed < 140) {
        KP = 0.00198; // 0.001974
        KD = 0.16;    // 0.02655
    } else if (speed >= 140 && speed < 150) {
        KP = 0.0016;
        KD = 0.15; // 0.16
    } else if (speed >= 150 && speed < 160) {
        KP = 0.0013;
        KD = 0.13;
    } else if (speed >= 160 && speed < 170) {
        KP = 0.00125;
        KD = 0.10;
    } else if (speed >= 170 && speed < 180) {
        KP = 0.00128;
        KD = 0.105;
    } else if (speed >= 180 && speed < 190) {
        KP = 0.0006; // 0.001
        KD = 0.105;  // 0.3
    } else if (speed >= 190 && speed < 200) {
        // KP = 0.00075;
        KP = 0.00125;
        KD = 0.09;
    }
    Trace();
}
/**
 * @brief 加速巡线
 * @param start 起始速度
 * @param end 结束速度
 */
void speed_up(int start, int end)
{
    KP = 0.0019;
    KD = 0.15;
    for (; start < end; start++) {
        if (speed <= 100) {
            KP = 0.003;
            KD = 0.16;
        } else {
            KP = 0.0016;
            KD = 0.15;
        }
        speed = start;
        // KP    = 0.0016;
        // KD    = 0.13;
        get_huidu_va();
        // Trace();
        Trace_transVelocity();
        if (start % 2 == 0) {
            Delay_ms(3);
        }
    }
}
/**
 * @brief 减速巡线
 * @param high 起始速度
 * @param low 结束速度
 */
void speed_down(int high, int low)
{
    for (; high > low; high--) {
        // if (speed < 50) {
        //     KP = 0.004;  // 0.005
        //     KD = 0.0025; // 0.05
        // } else if (speed >= 50 && speed < 70) {
        //     KP = 0.00197; // 0.025
        //     KD = 0.0130;
        // } else if (speed >= 70 && speed <= 85) {
        //     KP = 0.00186;
        //     KD = 0.0130;
        // } else if (speed >= 86 && speed < 100) {
        //     KP = 0.00172;
        //     KD = 0.0140;
        // } else if (speed >= 100 && speed < 140) {
        //     KP = 0.0016;
        //     KD = 0.0160;
        // } else if (speed >= 140 && speed < 160) {
        //     KP = 0.00157;
        //     KD = 0.0180;
        // } else if (speed >= 160 && speed <= 180) {
        //     KP = 0.00154;
        //     KD = 0.0200;
        // } else if (speed > 180 && speed <= 200) {
        //     KP = 0.00148;
        //     KD = 0.0255;
        // } else if (speed > 200 && speed <= 220) {
        //     KP = 0.00055;
        //     KD = 0.04;
        // }
        speed = high;
        if (speed <= 100) {
            KP = 0.002;
            KD = 0.16;
        } else {
            KP = 0.0012;
            KD = 0.12;
        }
        get_huidu_va();
        if (high % 2 == 0) Trace_transVelocity();
        Delay_ms(5);
    }
}
/**
 * @brief 爬坡加速巡线
 * @param start 起始速度
 * @param end 结束速度
 */
void speed_up_high(int start, int end)
{
    KP = 0.019;
    KD = 0.15;
    for (; start < end; start++) {
        if (speed <= 100) {
            KP = 0.04;
            KD = 0.15;
        } else {
            KP = 0.06;
            KD = 0.14;
        }
        speed = start;
        // KP    = 0.0016;
        // KD    = 0.13;
        get_huidu_va();
        // Trace();
        Trace_transVelocity();
        if (start % 2 == 0) {
            Delay_ms(5);
        }
    }
}
/**
 * @brief 爬坡减速巡线
 * @param high 起始速度
 * @param low 结束速度
 */
void speed_down_high(int high, int low)
{
    for (; high > low; high--) {
        // if (speed < 50) {
        //     KP = 0.004;  // 0.005
        //     KD = 0.0025; // 0.05
        // } else if (speed >= 50 && speed < 70) {
        //     KP = 0.00197; // 0.025
        //     KD = 0.0130;
        // } else if (speed >= 70 && speed <= 85) {
        //     KP = 0.00186;
        //     KD = 0.0130;
        // } else if (speed >= 86 && speed < 100) {
        //     KP = 0.00172;
        //     KD = 0.0140;
        // } else if (speed >= 100 && speed < 140) {
        //     KP = 0.0016;
        //     KD = 0.0160;
        // } else if (speed >= 140 && speed < 160) {
        //     KP = 0.00157;
        //     KD = 0.0180;
        // } else if (speed >= 160 && speed <= 180) {
        //     KP = 0.00154;
        //     KD = 0.0200;
        // } else if (speed > 180 && speed <= 200) {
        //     KP = 0.00148;
        //     KD = 0.0255;
        // } else if (speed > 200 && speed <= 220) {
        //     KP = 0.00055;
        //     KD = 0.04;
        // }
        speed = high;
        if (speed <= 100) {
            KP = 0.02;
            KD = 0.16;
        } else {
            KP = 0.012;
            KD = 0.12;
        }
        get_huidu_va();
        if (high % 2 == 0) Trace_transVelocity();
        Delay_ms(5);
    }
}
/**
 * @brief 桥巡线函数
 * @param mode 模式
 */
void bridge_Trace(uint8_t mode)
{
    if (mode == 1) {
        Gray_sum = Huidu_va(0) * (1) + Huidu_va(1) * (2) + Huidu_va(2) * (3) + Huidu_va(3) * (4) + Huidu_va(4) * (5) + Huidu_va(5) * (6) +
                   Huidu_va(11) * (-1) + Huidu_va(10) * (-2) + Huidu_va(9) * (-3) + Huidu_va(8) * (-4) + Huidu_va(7) * (-5) + Huidu_va(6) * (-6);
        error = Gray_sum * 1.0 * (3000.0 / sum * 1.0);
    } else if (mode == 2) {
        Gray_sum = Huidu_va(0) * (2) + Huidu_va(1) * (2) + Huidu_va(2) * (2) + Huidu_va(3) * (2) + Huidu_va(4) * (3) + Huidu_va(5) * (3) +
                   Huidu_va(11) * (-2) + Huidu_va(10) * (-2) + Huidu_va(9) * (-2) + Huidu_va(8) * (-2) + Huidu_va(7) * (-3) + Huidu_va(6) * (-3);
        error = Gray_sum * 1.0 * (3000.0 / sum * 1.0);
    }

    motorSpeed = KP * error + KD * (error - lastError);
    lastError  = error;

    mSpeed_right = speed + motorSpeed; // 右轮速度
    mSpeed_left  = speed - motorSpeed; // 左轮速度
    lastm1Speed  = mSpeed_right;
    lastm2Speed  = mSpeed_left;
    // 限幅
    if (mSpeed_right < 0) {
        mSpeed_right = 0;
    } else if (mSpeed_right > (1.5 * speed)) {
        mSpeed_right = 1.5 * speed;
    }

    if (mSpeed_left < 0) {
        mSpeed_left = 0;
    } else if (mSpeed_left > (1.5 * speed)) {
        mSpeed_left = 1.5 * speed;
    }
    set_pwm(1, mSpeed_right, speed);
    set_pwm(2, mSpeed_left, speed);
}

/**
 * @brief 桥上巡线
 *
 * @param N 速度
 * @param mode 模式,不同权值
 */
void bridge_PD(int N, uint8_t mode)
{
    get_huidu_va();
    speed = N;
    if (mode == 1) {
        KP = 0.015; // 0.015
        KD = 0.15;
    } else if (mode == 2) {
        KP = 0.009;
        KD = 0.2;
    }
    bridge_Trace(mode);
}
/**
 * @brief 无线直走函数
 */
void Straight_run(int speed)
{
    if (JD > 180) {
        JD = JD - 360;
    }
    if (-2 < JD && JD < 2) {
        Run(speed);
    } else if (JD > 0) {
        if (JD < 6) {
            run(speed + 3, speed);
        } else if (JD < 10) {
            run(speed + 10, speed);
        }
    } else if (JD < 0) {
        if (JD > -6) {
            run(speed, speed + 3);
        } else if (JD > -10) {
            run(speed, speed + 10);
        }
    }
}

void Straight_run_back(int speed)
{
    if (JD > 180) {
        JD = JD - 360;
    }
    if (-2 < JD && JD < 2) {
        Run(-speed);
    } else if (JD > 0) {
        if (JD < 5) {
            run(-speed - 3, -speed);
        } else if (JD < 10) {
            run(-speed - 10, -speed);
        }
    } else if (JD < 0) {
        if (JD > -5) {
            run(-speed, -speed - 3);
        } else if (JD > -10) {
            run(-speed, -speed - 10);
        }
    }
}

/**
 * @brief 无白线直走
 */
void Straight(int time)
{
    HWT101_to_0();
    Stop(40);
    Deg_IN();
    t3_i = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    do {
        Straight_run(50);
    } while (Huidu_va(10) < white[10] || Huidu_va(11) < white[11] || t3_i > time);
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    t3_i = 0;
}

void Straight_back(void)
{
    Front_up();
    Stop(250);
    HWT101_to_0();
    Stop(200);
    Deg_IN();
    t3_i = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    while (t3_i < 800) {
        Straight_run_back(45);
        if (hdxl == 0 || hdxr == 0) break;
    }
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    t3_i = 0;

    t3_i = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    do {
        Straight_run_back(45);
        // if(hdxl == 0 || hdxr == 0) break;
    } while (t3_i < 300);
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    t3_i = 0;
    stop();
}

void txs_trace(void)
{
    int jd = compass_b();
    if (jd < 180) {
        run_delay(50 + jd * 2, 50 - jd * 2, 10);
    } else if (jd > 180) {
        run_delay(50 - (360 - jd) * 2, 50 + (360 - jd) * 2, 10);
    } else
        run_delay(50, 50, 10);
}
