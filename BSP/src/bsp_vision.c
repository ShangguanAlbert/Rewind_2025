#include "bsp_vision.h"

int openmv[4];
int8_t OpenMV;
int m = 0;

/**
 * @brief 串口5初始化函数, 并且开启NVIC中断配置 115200
 */
void USART5_OpenMV_Init(void)
{
    // GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // 串口5对应引脚复用映射
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  // 使能GPIOD时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  // 使能GPIOc时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE); // 使能UART5时钟

    // USART5端口配置
    /* PC12用于TX数据输出, PD2用于RX数据输入 */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // USART3 初始化设置
    USART_InitStructure.USART_BaudRate            = 115200;                         // 波特率设置
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;            // 字长为8位数据格式
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;               // 一个停止位
    USART_InitStructure.USART_Parity              = USART_Parity_No;                // 无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件数据流控制
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;  // 收发模式
    USART_Init(UART5, &USART_InitStructure);                                       // 初始化串口3

    USART_Cmd(UART5, ENABLE); // 使能串口2

    // Usart3 NVIC 配置
    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE); // 开启接收中断

    NVIC_InitStructure.NVIC_IRQChannel                   = UART5_IRQn; // 串口5中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;           // 抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;           // 子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;      // IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                                     // 根据指定的参数初始化NVIC寄存器
}

void Openmv_Data(void)
{
    OpenMV = openmv[2];
}

#if cmd == 0x5b
void Openmv_Receive_Data(int16_t data)
{
    static uint8_t state = 0;
    if (state == 0 && data == 0xb3) {
        state     = 1;
        openmv[0] = data;
    } else if (state == 1 && data == 0xb2) {
        state     = 2;
        openmv[1] = data;
    } else if (state == 2) {
        state     = 3;
        openmv[2] = data;
    } else if (state == 3) {
        if (data == 0x5b) {
            state     = 0;
            openmv[3] = data;
            Openmv_Data();
            data = 0;
        } else if (data != 0x5b) {
            state = 0;
            for (m = 0; m < 4; m++) {
                openmv[m] = 0x00;
            }
        }
    } else {
        state = 0;
        data  = 0;
        for (m = 0; m < 4; m++) {
            openmv[m] = 0x00;
        }
    }
}
#else
void Openmv_Receive_Data(int16_t data)
{
    static uint8_t state = 0;
    if (state == 0 && data == 0xb3) {
        state     = 1;
        openmv[0] = data;
    } else if (state == 1 && data == 0xb2) {
        state     = 2;
        openmv[1] = data;
    } else if (state == 2) {
        state     = 3;
        openmv[2] = data;
    } else if (state == 3) {
        if (data == 0xb5) {
            state     = 0;
            openmv[3] = data;
            Openmv_Data();
            data = 0;
        } else if (data != 0xb5) {
            state = 0;
            for (m = 0; m < 4; m++) {
                openmv[m] = 0x00;
            }
        }
    } else {
        state = 0;
        data  = 0;
        for (m = 0; m < 4; m++) {
            openmv[m] = 0x00;
        }
    }
}
#endif

void UART5_IRQHandler(void) // 串口5中断服务程序
{
    uint8_t com_data;
    if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) {
        USART_ClearFlag(UART5, USART_FLAG_RXNE);
        com_data = USART_ReceiveData(UART5);
        Openmv_Receive_Data(com_data);
        Openmv_Data();
        com_data = 0;
    }
}

/**
 * @brief 发送指令：识别宝物颜色
 */
void Detect_Color(void)
{
    while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
    USART_SendData(UART5, 0xb3);
    while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
    USART_SendData(UART5, 0xb2);
    while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
    USART_SendData(UART5, 0x00);
    while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
    USART_SendData(UART5, 0Xb5);
}

/**
 * @brief 发送指令：识别宝物位置
 */
void Locate_treasure(void)
{
    while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
    USART_SendData(UART5, 0xb3);
    while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
    USART_SendData(UART5, 0xb2);
    while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
    USART_SendData(UART5, 0x11);
    while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
    USART_SendData(UART5,0Xb5);
}

/**
 * @brief 发送指令：闭嘴
 */
void SHUT_UP(void)
{
    while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
    USART_SendData(UART5, 0xb3);
    while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
    USART_SendData(UART5, 0xb2);
    while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
    USART_SendData(UART5, 0x22);
    while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
    USART_SendData(UART5, 0Xb5);
}
