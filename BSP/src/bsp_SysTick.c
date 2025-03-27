#include "bsp_SysTick.h"

/**
 * @brief us延时倍乘数
 *
 */
static uint8_t fac_us = 0;
/**
 * @brief ms延时倍乘数
 *
 */
static uint16_t fac_ms = 0;

/**
 * @brief 初始化系统滴答定时器 SysTick
 * @param  无
 * @retval 无
 * @note   系统滴答定时器 SysTick 时钟源为 HCLK/8
 *         1. 1ms 加载值计算: (72MHz / 8) / 1000 = 9000
 *         2. 1us 加载值计算: (72MHz / 8) / 1000000 = 9
 *         3. 1ms 加载值计算: (72MHz / 8) / 1000000 = 9000
 *         4. 1s 加载值计算: (72MHz / 8) = 9000000
 */
void SysTick_Init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); // 选择外部时钟  HCLK/8
    fac_us = SystemCoreClock / 8000000;                   // 为系统时钟的1/8
    fac_ms = (uint16_t)fac_us * 1000;                     // 非OS下,代表每个ms需要的systick时钟数
}

/**
 * @brief 微秒级延时
 * @param nus 延时时长，范围：0~798915(最大值即2^24/fac_us@fac_us=21)
 * @retval 无
 */
void delay_us(uint32_t nus)
{
    uint32_t temp;
    SysTick->LOAD = nus * fac_us;             // 时间加载
    SysTick->VAL  = 0x00;                     // 清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // 开始倒数
    do {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16))); // 等待时间到达
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 关闭计数器
    SysTick->VAL = 0X00;                       // 清空计数器
}

/**
 * @brief 毫秒级延时
 * @param nms the delay time, range: 0~1864 (maximum value is 2^24/fac_ms@fac_ms=21)
 */
void delay_ms(uint16_t nms)
{
    uint32_t temp;
    SysTick->LOAD = (uint32_t)nms * fac_ms;   // 时间加载(SysTick->LOAD为24bit)
    SysTick->VAL  = 0x00;                     // 清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // 开始倒数
    do {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16))); // 等待时间到达
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 关闭计数器
    SysTick->VAL = 0X00;                       // 清空计数器
}

/**
 * @brief  微秒级延时
 * @param  xus 延时时长，范围：0~233015
 * @retval 无
 */
void Delay_us(uint32_t xus)
{
    SysTick->LOAD = 72 * xus;              // 设置定时器重装值
    SysTick->VAL  = 0x00;                  // 清空当前计数值
    SysTick->CTRL = 0x00000005;            // 设置时钟源为HCLK，启动定时器
    while (!(SysTick->CTRL & 0x00010000)); // 等待计数到0
    SysTick->CTRL = 0x00000004;            // 关闭定时器
}

/**
 * @brief  毫秒级延时
 * @param  xms 延时时长，范围：0~4294967295
 * @retval 无
 */
void Delay_ms(uint32_t xms)
{
    while (xms--) {
        Delay_us(1000);
    }
}

/**
 * @brief  秒级延时
 * @param  xs 延时时长，范围：0~4294967295
 * @retval 无
 */
void Delay_s(uint32_t xs)
{
    while (xs--) {
        Delay_ms(1000);
    }
}