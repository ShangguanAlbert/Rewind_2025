#include "bsp_compass.h"

SAngle stcAngle;

double compass_float;
float compass_data;

uint8_t shujv;
uint8_t Start_Receiving;
uint8_t data[11];
uint16_t cnt_m = 0;
float JD;
float XJD;

/**
 * @brief 指南针HWT101串口通讯初始化
 * @param bound 波特率115200
 */
void USART2_COMPASS_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);

    /* PD5用于TX数据输出, PD6用于RX数据输入 */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /*USART初始化*/
    USART_InitStructure.USART_BaudRate            = 115200;                         // 波特率
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 硬件流控制，不需要
    USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;  // 模式，发送模式和接收模式均选择
    USART_InitStructure.USART_Parity              = USART_Parity_No;                // 奇偶校验，不需要
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;               // 停止位，选择1位
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;            // 字长，选择8位
    USART_Init(USART2, &USART_InitStructure);                                       // 将结构体变量交给USART_Init，配置USART1

    /*中断输出配置*/
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // 开启串口接收数据的中断

    /*NVIC配置*/
    NVIC_InitStructure.NVIC_IRQChannel                   = USART2_IRQn; // 选择配置NVIC的USART1线
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;      // 指定NVIC线路使能
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;           // 指定NVIC线路的抢占优先级为1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;           // 指定NVIC线路的响应优先级为1
    NVIC_Init(&NVIC_InitStructure);                                     // 将结构体变量交给NVIC_Init，配置NVIC外设

    /*USART使能*/
    USART_Cmd(USART2, ENABLE); // 使能USART1，串口开始运行
}

void USART2_IRQHandler(void)
{
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) { // 接收中断
        CopeSerial2Data((unsigned char)USART2->DR);          // 接收数据
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        shujv = USART_ReceiveData(USART2);
        if (shujv == 0x55) // 帧头
        {
            Start_Receiving = 1;
        }
        if (Start_Receiving == 1) {
            data[cnt_m] = shujv;
            cnt_m++;
            if (cnt_m == 11) // 接受完毕，停止接收
            {
                Start_Receiving = 0;
                cnt_m           = 0;
                if (data[1] == 0x53) // 进入了0x53数据包
                {
                    XJD = (short)((data[7] << 8) | data[6]) / 32768.0 * 180;
                    JD  = (float)((data[7] << 8) | data[6]) / 32768 * 180;
                }
            }
        }
    }
    USART_ClearITPendingBit(USART2, USART_IT_ORE);
}

/**
 * @brief 解包HWT101数据包,并且返回对应角度
 * @param ucData 读取DR寄存器的数据
 */
void CopeSerial2Data(unsigned char ucData)
{
    static unsigned char ucRxBuffer[250];
    static unsigned char ucRxCnt = 0;

    ucRxBuffer[ucRxCnt++] = ucData;
    if (ucRxBuffer[0] != 0x55) // 校验数据头
    {
        ucRxCnt = 0;
        return;
    }
    if (ucRxCnt < 11) { return; } // 判断一帧数据是否接收完成
    else {
        switch (ucRxBuffer[1]) {
            case 0x53:
                memcpy(&stcAngle, &ucRxBuffer[2], 8);
                break; // 判断是否为角度的数据
        }
        ucRxCnt = 0;
    }
}
/**
 * @brief HWT101 指令置零
 */
void HWT101_to_0(void)
{
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
    USART_SendData(USART2, 0XFF);
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
    USART_SendData(USART2, 0XAA);
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
    USART_SendData(USART2, 0X76);
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
    USART_SendData(USART2, 0X00);
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
    USART_SendData(USART2, 0X00);
}
/**
 * @brief 调用读取指南针数据,指南针断电再上电之后自动初始化校准.
 * @return compass_data 指南针数据
 */
float compass_b(void)
{
    compass_float = (double)stcAngle.Angle[2] / 32768.0 * 180;
    if ((float)compass_float < 0) {
        compass_data = 360 + (float)compass_float;
    } else {
        compass_data = (float)compass_float;
    }
    return compass_data;
}