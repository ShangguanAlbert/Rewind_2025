#include "bsp_sensor.h"

uint8_t res_hw;
uint8_t res_hdlr;

/**
 * @brief 红外初始化 左红外PE0
 *
 */
void GPIO_HW_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;    // 下拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度选择
    // 初始化 PE0 引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    // 初始化 PE3 引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/**
 * @brief 读取红外数字电平
 *
 * @param[in] LR 1-左;2-右.
 * @return uint8_t 数字电平
 */
uint8_t HW(uint8_t LR)
{
    if (LR == 1) {
        res_hw = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0);
    }
    if (LR == 2) {
        res_hw = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3);
    }
    return res_hw;
}
/**
 * @brief 左右灰度初始化
 *
 */
void GPIO_HDLR_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;    // 下拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度选择
    // 初始化 PE1 引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    // 初始化 PE2 引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
}
/**
 * @brief 读取腰灯信号
 *
 * @param[in] LR 1-左;2-右.
 * @return uint8_t 数字电平
 */
uint8_t HDLR(uint8_t LR)
{
    if (LR == 1) {
        res_hdlr = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1);
    }
    if (LR == 2) {
        res_hdlr = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2);
    }
    return res_hdlr;
}
