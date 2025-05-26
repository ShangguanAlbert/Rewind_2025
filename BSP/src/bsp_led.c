#include "bsp_led.h"
#include "bsp_SysTick.h"

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; // 输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度选择

    // 初始化 PE0 引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
}
/**
 * @brief 打开LED1
 */
void LED_ON(void)
{
    GPIO_SetBits(GPIOE, GPIO_Pin_5); // 低电平点亮LED
}

/**
 * @brief 关闭LED1
 */
void LED_OFF(void)
{
    GPIO_ResetBits(GPIOE, GPIO_Pin_5); // 高电平熄灭LED
}
/**
 * @brief LED1闪烁指定次数
 * @param times 闪烁次数
 * @param on_time 每次亮的时间(毫秒)
 * @param off_time 每次灭的时间(毫秒)
 */
/**
 * @brief LED1闪烁指定次数
 */
void LED_Blink(void)
{
    LED_ON();
    Delay_ms(500);
    LED_OFF();
    Delay_ms(500);
    LED_ON();
    Delay_ms(500);
    LED_OFF();
}
