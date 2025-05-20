#include "bsp_servo.h"
#include "bsp_SysTick.h"
/**
 * @brief 初始化舵机
 *
 */
void TIM2_Servo_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    // 使能时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    // 重映射TIM2
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);

    // 配置PA15
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 配置PB3、PB10、PB11
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 基本定时器配置
    TIM_TimeBaseStructure.TIM_Period        = 20000 - 1; // 20ms周期
    TIM_TimeBaseStructure.TIM_Prescaler     = 72 - 1;    // 72MHz / 72 = 1MHz
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // PWM配置
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    // TIM_OCInitStructure.TIM_Pulse       = 1500; // 1.5ms中位脉宽
    TIM_OCInitStructure.TIM_Pulse      = 0; // 0.5ms最小脉宽
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM2, &TIM_OCInitStructure); // PA15
    TIM_OC2Init(TIM2, &TIM_OCInitStructure); // PB3
    TIM_OC3Init(TIM2, &TIM_OCInitStructure); // PB10
    TIM_OC4Init(TIM2, &TIM_OCInitStructure); // PB11

    // 使能预装载
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);

    // 使能定时器
    TIM_Cmd(TIM2, ENABLE);

    // 使能PWM输出
   
    TIM2->CCR3 =2500;//夹子舵机 张开最大2500
    TIM2->CCR4 = 2145;//前铲舵机

}
/**
 * @brief 设置舵机角度
 * @param channel 通道
 * @param angle 角度
 */
void Servo_SetAngle(uint8_t channel, uint16_t angle)
{
    uint16_t pulse = 500 + angle * 2000 / 180;
    switch (channel) {
        case 1:
            TIM_SetCompare1(TIM2, pulse);
            break;
        case 2:
            TIM_SetCompare2(TIM2, pulse);
            break;
        case 3:
            TIM_SetCompare3(TIM2, pulse);
            break;
        case 4:
            TIM_SetCompare4(TIM2, pulse);
            break;
        default:
            break;
    }
}