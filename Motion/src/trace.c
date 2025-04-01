#include "trace.h"

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

int32_t thr_whiteline[] = thr_line;
int32_t white[]         = thr_white;
int32_t green[]         = thr_green;

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

void Trace(void)
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
    } else if (cnt_whiteline >= 3) {
        error = 0;
    } else {
        Gray_sum = Huidu_va(0) * (3) +
                   Huidu_va(1) * (5) + Huidu_va(2) * (4) + Huidu_va(3) * (3) + Huidu_va(4) * (2) +
                   Huidu_va(5) * (1) + Huidu_va(6) * (-1) +
                   Huidu_va(7) * (-2) + Huidu_va(8) * (-3) + Huidu_va(9) * (-4) + Huidu_va(10) * (-5) +
                   Huidu_va(11) * (-3);
        error = Gray_sum * 1.0 * (2800.0 / sum * 1.0);
    }

    motorSpeed   = KP * error + KD * (error - lastError);
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
        } else if (mSpeed_right > (1.25 * speed)) {
            mSpeed_right = 1.25 * speed;
        }

        if (mSpeed_left < 0) {
            mSpeed_left = 0;
        } else if (mSpeed_left > (1.25 * speed)) {
            mSpeed_left = 1.25 * speed;
        }
    }

    set_pwm(1, mSpeed_right, speed);
    set_pwm(2, mSpeed_left, speed);
}

void slow_run(int N)
{
    get_huidu_va();
    speed = N;
    if (speed < 50) {
        KP = 0.0035;
        KD = 0.05;
    } else if (speed >= 50 && speed < 60) { // 50
        KP = 0.002;
        KD = 0.007;
    } else if (speed >= 60 && speed < 70) { // 60
        KP = 0.00225;
        KD = 0.005;
    } else if (speed >= 70 && speed < 80) { // 70
        KP = 0.00234;
        KD = 0.0055;
    } else if (speed >= 80 && speed < 90) { // 80
        KP = 0.0024;
        KD = 0.00665;
    } else if (speed >= 90) { // 90
        KP = 0.0025;
        KD = 0.0073;
    }
    Trace();
}

void high_run(int N)
{
    get_huidu_va();
    speed = N;
    if (speed > 90 && speed < 100) {
        KP = 0.002;  // p大会抽会扭
        KD = 0.0055; // d小回到白线的速度就慢
    } else if (speed >= 100 && speed < 110) {
        KP = 0.0020;
        KD = 0.0264;
    } else if (speed >= 110 && speed < 120) {
        KP = 0.001985;
        KD = 0.02645;
    } else if (speed >= 120 && speed < 130) {
        KP = 0.001974;
        KD = 0.02644;
    } else if (speed >= 130 && speed < 140) {
        KP = 0.0019735;
        KD = 0.02647;
    } else if (speed >= 140 && speed < 150) {
        KP = 0.001984;
        KD = 0.02643;
    } else if (speed >= 150 && speed < 160) {
        KP = 0.001980;
        KD = 0.02643;
    } else if (speed >= 160 && speed < 170) {
        KP = 0.0019808;
        KD = 0.026441;
    } else if (speed >= 170 && speed < 180) {
        KP = 0.00197;
        KD = 0.026477;
    } else if (speed >= 180 && speed < 190) {
        KP = 0.002315;
        KD = 0.0264;
    } else if (speed >= 190 && speed < 200) {
        KP = 0.002360;
        KD = 0.02653;
    }
    Trace();
}

void speed_up(int start, int end)
{
    KP = 0.00225;
    KD = 0.025;
    for (; start < end; start++) {
        if (speed < 100) {
            KP = 0.006;
            KD = 0.02;
        } else {
            KP = 0.003;
            KD = 0.05;
        }
        speed = start;
        get_huidu_va();
        Trace();
        if (start % 10 == 0) {
            Delay_ms(1);
        }
    }
}

void speed_down(int high, int low)
{
    for (; high > low; high--) {
        if (speed < 50) {
            KP = 0.004;  // 0.005
            KD = 0.0025; // 0.05
        } else if (speed >= 50 && speed < 70) {
            KP = 0.00197; // 0.025
            KD = 0.0130;
        } else if (speed >= 70 && speed <= 85) {
            KP = 0.00186;
            KD = 0.0130;
        } else if (speed >= 86 && speed < 100) {
            KP = 0.00172;
            KD = 0.0140;
        } else if (speed >= 100 && speed < 140) {
            KP = 0.0016;
            KD = 0.0160;
        } else if (speed >= 140 && speed < 160) {
            KP = 0.00157;
            KD = 0.0180;
        } else if (speed >= 160 && speed <= 180) {
            KP = 0.00154;
            KD = 0.0200;
        } else if (speed > 180 && speed <= 200) {
            KP = 0.00148;
            KD = 0.0255;
        } else if (speed > 200 && speed <= 220) {
            KP = 0.00055;
            KD = 0.04;
        }
        speed = high;
        get_huidu_va();
        if (high % 5 == 0) Trace();
        Delay_ms(1);
    }
}