#include "bsp_timer.h"

uint32_t t3_i;
uint32_t t7_i;

void TIM3_TurnPID_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseStructure.TIM_Prescaler     = 7200 - 1;
    TIM_TimeBaseStructure.TIM_Period        = 10 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; // 设置向上计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

    NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM3, ENABLE);
}

void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update)) {
        t3_i++;
    }
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update); // 清除更新中断标志位
}

void TIM7_Reset_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

    TIM_TimeBaseStructure.TIM_Period        = 10 - 1;  // 自动装载值
    TIM_TimeBaseStructure.TIM_Prescaler     = 7200 - 1; // 分频系数
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; // 设置向上计数模式
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIM7, TIM_IT_Update, DISABLE);
    TIM_ClearITPendingBit(TIM7, TIM_IT_Update);

    NVIC_InitStructure.NVIC_IRQChannel                   = TIM7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM7, ENABLE);
}

void TIM7_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM7, TIM_IT_Update)) {
        t7_i++;
    }
    TIM_ClearITPendingBit(TIM7, TIM_IT_Update); // 清除更新中断标志位
}