#include "bsp_timer.h"

uint32_t t3_i;

void TIM3_TurnPID_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseStructure.TIM_Prescaler     = 3600 - 1;
    TIM_TimeBaseStructure.TIM_Period        = 100 - 1;
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