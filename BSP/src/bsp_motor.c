/**
 * @file bsp_motor.c
 * @author sgfz (sgfz_work@163.com)
 * @brief 得科电机驱动 TIM8_CH1-4 PC6-9
 * @version 0.1
 * @date 2025-03-13
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "bsp_motor.h"
#include "bsp_SysTick.h"

float mdif_res;

/**
 * @brief 直流减速电机初始化
 *
 */
void TIM8_Motor_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;  // 复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度100MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // TIM_TimeBaseStructure.TIM_Prescaler     = 68 - 1;             // 定时器分频
    // TIM_TimeBaseStructure.TIM_Period        = 250;                // 自动重装载值
    TIM_TimeBaseStructure.TIM_Prescaler         = 30;                 // 定时器分频
    TIM_TimeBaseStructure.TIM_Period            = 236;                // 自动重装载值
    TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up; // 向上计数模式
    TIM_TimeBaseStructure.TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; // 高级定时器特有
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);  // 初始化定时器8

    // 初始化TIM1 Channel1 PWM模式
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM2;        // 选择定时器模式:TIM脉冲宽度调制模式1
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable; // 比较输出使能
    TIM_OCInitStructure.TIM_Pulse        = 0;                      // 初始脉冲为0
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_Low;     // 输出极性:TIM输出比较极性低
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset; // 互补输出开启
    TIM_OC1Init(TIM8, &TIM_OCInitStructure);                       // 根据T指定的参数初始化外设TIM8 OC1

    // 初始化TIM1 Channel2 PWM模式
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM2;        // 选择定时器模式:TIM脉冲宽度调制模式1
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable; // 比较输出使能
    TIM_OCInitStructure.TIM_Pulse        = 0;                      // 初始脉冲为0
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_Low;     // 输出极性:TIM输出比较极性低
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset; // 互补输出开启
    TIM_OC2Init(TIM8, &TIM_OCInitStructure);                       // 根据T指定的参数初始化外设TIM8 OC2

    // 初始化TIM1 Channel3 PWM模式
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM2;        // 选择定时器模式:TIM脉冲宽度调制模式1
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable; // 比较输出使能
    TIM_OCInitStructure.TIM_Pulse        = 0;                      // 初始脉冲为0
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_Low;     // 输出极性:TIM输出比较极性低
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset; // 互补输出开启
    TIM_OC3Init(TIM8, &TIM_OCInitStructure);                       // 根据T指定的参数初始化外设TIM8 OC3

    // 初始化TIM1 Channel4 PWM模式
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM2;        // 选择定时器模式:TIM脉冲宽度调制模式1
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable; // 比较输出使能
    TIM_OCInitStructure.TIM_Pulse        = 0;                      // 初始脉冲为0
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_Low;     // 输出极性:TIM输出比较极性低
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset; // 互补输出开启
    TIM_OC4Init(TIM8, &TIM_OCInitStructure);                       // 根据T指定的参数初始化外设TIM8 OC4

    TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable); // 使能TIM8在CCR1上的预装载寄存器
    TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable); // 使能TIM8在CCR2上的预装载寄存器
    TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable); // 使能TIM8在CCR3上的预装载寄存器
    TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable); // 使能TIM8在CCR4上的预装载寄存器

    TIM_ARRPreloadConfig(TIM8, ENABLE); // ARPE使能
    TIM_Cmd(TIM8, ENABLE);              // 使能TIM8

    /* 主输出使能 */
    TIM_CtrlPWMOutputs(TIM8, ENABLE); // 主输出使能; 注意：高级定时器相比通用定时器，程序上，需要增加这一行，否则不工作;

    TIM_SetCompare1(TIM8, 0);
    TIM_SetCompare2(TIM8, 0);
    TIM_SetCompare3(TIM8, 0);
    TIM_SetCompare4(TIM8, 0);
}
/**
 * @brief 设定左右电机速度,可变轮差,用于盲走
 * @param port 1-右电机;2-左电机
 * @param speed 设置速度, 限幅210
 */
void Motor(uint8_t port, int speed)
{
    if (speed >= 0) {
        if (speed > 220) speed = 220;
        switch (port) {
            case 1: // 右边轮子正转
                TIM8->CCR1 = speed * m_diff(speed);
                TIM8->CCR2 = 0;
                break;
            case 2: // 左边轮子正转
                TIM8->CCR3 = 0;
                TIM8->CCR4 = speed;
                break;
        }
    } else {
        if (speed < -220) speed = -220;
        switch (port) {
            case 1: // 右边轮子反转
                TIM8->CCR1 = 0;
                TIM8->CCR2 = -speed * m_diff(speed);
                break;
            case 2: // 左边轮子反转
                TIM8->CCR3 = -speed;
                TIM8->CCR4 = 0;
                break;
        }
    }
}
/**
 * @brief 设定左右电机速度,动态可变轮差,用于高速巡线
 * @param port 1-右电机;2-左电机
 * @param speed 设置速度, 限幅245
 * @param set_speed 确定此速度下的轮差
 */
void set_pwm(uint8_t port, int speed, int set_speed)
{
    if (speed >= 0) {
        if (speed > 225) speed = 225;
        switch (port) {
            case 1: // 右边轮子正转
                TIM8->CCR1 = speed * m_diff(set_speed);
                TIM8->CCR2 = 0;
                break;
            case 2: // 左边轮子转
                TIM8->CCR3 = 0;
                TIM8->CCR4 = speed;
                break;
        }
    } else {
        if (speed < -225) speed = -225;
        switch (port) {
            case 1: // 右边轮子反转
                TIM8->CCR1 = 0;
                TIM8->CCR2 = -speed * m_diff(set_speed);
                break;
            case 2: // 左边轮子转
                TIM8->CCR3 = -speed;
                TIM8->CCR4 = 0;
                break;
        }
    }
}
/**
 * @brief 对应速度下的轮差系数
 * @param speed 设定的速度
 * @return float mdif_res 对应轮差系数
 */
float m_diff(int speed)
{
    if (speed <= 50) {
        mdif_res = 0.958;//
    } else if (speed > 50 && speed <= 60) {
        mdif_res = 0.96;
    } else if (speed > 60 && speed <= 75) {
        mdif_res = 0.967;
    } else if (speed > 75 && speed <= 80) {
        mdif_res = 0.976;//
    } else if (speed > 80 && speed <= 90) {
        mdif_res = 0.968;
    } else if (speed > 90 && speed <= 95) {
        mdif_res = 0.966;
    } else if (speed > 95 && speed <= 105) {
        mdif_res = 0.965;
    } else if (speed > 105 && speed < 120) {
        mdif_res = 0.964;
    } else if (speed >= 120 && speed <= 130) {
        mdif_res = 0.958;
    } else if (speed > 130 && speed <= 140) {
        mdif_res = 0.965;//
    } else if (speed > 140 && speed < 160) {
        mdif_res = 0.96;
    } else if (speed >= 160 && speed < 170) {
        mdif_res = 0.9676;
    } else if (speed >= 170 && speed < 180) {
        mdif_res = 0.975;
    } else if (speed >= 180 && speed < 185) {
        mdif_res = 0.9792;
    } else if (speed >= 185 && speed < 190) {
        mdif_res = 0.978;
    } else if (speed >= 190 && speed < 200) {
        mdif_res = 0.985;
    }
    return mdif_res;
}
