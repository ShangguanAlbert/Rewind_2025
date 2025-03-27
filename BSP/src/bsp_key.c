/**
 * @file bsp_key.c
 * @author Albert SG
 * @brief KEY PD10-SW8 PB5-SW9 PD11-SW4 摁下去接地 默认是高电平 IPU
 * @version 0.1
 * @date 2025-03-08
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "bsp_key.h"
#include "bsp_SysTick.h"

void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE);

    GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度选择

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t KEY_Scan(uint8_t mode)
{
    static u8 key_up = 1;
    if (mode) key_up = 1;
    if (key_up && (KeyUp == 0 || KeyDown == 0 || KeyConfirm == 0)) {
        delay_ms(10);
        key_up = 0;
        if (KeyUp == 0)
            return 1;
        else if (KeyDown == 0)
            return 3;
        else if (KeyConfirm == 0)
            return 2;
    } else if (KeyUp == 1 && KeyDown == 1 && KeyConfirm == 1) {
        key_up = 1;
    }
    return 0;
}
