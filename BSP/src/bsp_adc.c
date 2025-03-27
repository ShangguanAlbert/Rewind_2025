/**
 * @file bsp_adc.c
 * @author Albert Shangguan
 * @brief Initialize Ports of ADC1
 *        GPIO Pin: PA0 PA1 PA2 PA3 PC0  PC1  PC2  PC3  PC4  PC5  PB0 PB1
 *         Channel: CH0 CH1 CH2 CH3 CH10 CH11 CH12 CH13 CH14 CH15 CH8 CH9
 * @version 0.1
 * @date 2025-03-06
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "bsp_adc.h"
#include "bsp_SysTick.h"

volatile uint16_t ADCValue[12] = {0};

void ADC1_Huidu_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode       = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel       = 12;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 5, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 6, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 7, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 8, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 9, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 10, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 11, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 12, ADC_SampleTime_55Cycles5);

    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)ADCValue;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize         = 12;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    DMA_Cmd(DMA1_Channel1, ENABLE);
    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1) == SET);
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1) == SET);

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

/**
 * @brief 对采集的ADC值进行滤波 冒泡排序
 * @param num 第几个灰度通道
 * @return 平均之后的adc值
 */
uint32_t Filter(uint16_t num)
{
    int i, j;
    int filter_temp, filter_sum = 0;
    int filter_buf[5];
    for (i = 0; i < 5; i++) {
        filter_buf[i] = ADCValue[num]; // 连续测量同一通道的值5次
        // 此处的延时 得科没有 行知有 具体有待实测
        // 从理论上 有这个延时能够匹配adc的采集速度
        // 从实验效果上 有这个延时好像数据更新更快 波动更小
        delay_us(20);
    }
    for (j = 0; j < 4; j++) { // 冒泡排序 从小到大
        for (i = 0; i < 4 - j; i++) {
            if (filter_buf[i] > filter_buf[i + 1]) {
                filter_temp       = filter_buf[i];
                filter_buf[i]     = filter_buf[i + 1];
                filter_buf[i + 1] = filter_temp;
            }
        }
    }
    for (i = 1; i < 5 - 1; i++) {
        filter_sum += filter_buf[i]; // 取中间三次求平均
    }
    return filter_sum / (5 - 2);
}

/**
 * @brief 返回灰度值 右边1 左边11 从右到左
 * @param ch 第几个灰度 右边1 左边11
 * @return int32_t 灰度的数值
 */
int32_t Huidu_va(uint8_t ch)
{
    static volatile uint32_t Huidu_value;
    switch (ch) {
        case 0:
            Huidu_value = Filter(4);
            break;
        case 1:
            Huidu_value = Filter(5);
            break;
        case 2:
            Huidu_value = Filter(7);
            break;
        case 3:
            Huidu_value = Filter(6);
            break;
        case 4:
            Huidu_value = Filter(11);
            break;
        case 5:
            Huidu_value = Filter(3);
            break;
        case 6:
            Huidu_value = Filter(10);
            break;
        case 7:
            Huidu_value = Filter(2);
            break;
        case 8:
            Huidu_value = Filter(9);
            break;
        case 9:
            Huidu_value = Filter(1);
            break;
        case 10:
            Huidu_value = Filter(8);
            break;
        case 11:
            Huidu_value = Filter(0);
            break;
        default:
            Huidu_value = 0;
            break;
    }
    return Huidu_value;
}