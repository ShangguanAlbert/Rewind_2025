#include "bsp_led.h"

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; // 输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度选择

    // 初始化 PD0 和 PD1 引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_SetBits(GPIOD, GPIO_Pin_0);
    GPIO_SetBits(GPIOD, GPIO_Pin_1); // 设置初始状态为高电平（LED 熄灭）
}
