#include "bsp_qr.h"
#include "bsp_lcd.h"
#include "lcd_spi_130.h"
#include "bsp_timer.h"


#define QR_BUFFER_SIZE 50
#define QR_END_CHAR    0X0D // 结束符

// 数据结构
uint8_t qr_raw_data[QR_BUFFER_SIZE]; // 存储接收到的原始二维码数据
uint16_t qr_index     = 0;           // 当前索引位置
uint8_t qr_data_ready = 0;           // 数据接收完成标志
uint8_t qr_flag       = 0;
int32_t qr_value      = 0;

void UART4_QRCode_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

    USART_DeInit(UART4);

    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP; // tx
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; // rx
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_11;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    USART_InitStruct.USART_BaudRate            = 9600;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_Parity              = USART_Parity_No;
    USART_InitStruct.USART_StopBits            = USART_StopBits_1;
    USART_InitStruct.USART_WordLength          = USART_WordLength_8b;

    USART_Init(UART4, &USART_InitStruct);
    USART_Cmd(UART4, ENABLE);
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

    NVIC_InitStruct.NVIC_IRQChannel                   = UART4_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority        = 3;
    NVIC_Init(&NVIC_InitStruct);
}

void UART4_IRQHandler(void)
{
    uint8_t temp;

    if (USART_GetITStatus(UART4, USART_IT_RXNE)) {
        USART_ClearITPendingBit(UART4, USART_IT_RXNE);
        temp = USART_ReceiveData(UART4);

        // 保存数据
        if (qr_index < QR_BUFFER_SIZE - 1) {
            qr_raw_data[qr_index] = temp;
        }

        // 检测是否为结束字符或缓冲区已满
        if (temp == QR_END_CHAR || qr_index >= QR_BUFFER_SIZE - 1) {
            qr_raw_data[qr_index] = '\0'; // 字符串结束标志
            qr_data_ready = 1;    // 标记接收完成
            
            // 如果是数字，直接计算值并设置标志
            if (qr_raw_data[0] >= '0' && qr_raw_data[0] <= '9') {
                qr_value = QR_GetIntValue();
                if (qr_value != 0) {
                    qr_flag = 1;
                }
            }
        } else {
            qr_index++; // 更新索引
        }
    }
}

// 获取二维码数据
uint8_t *QR_GetData(void)
{
    return qr_raw_data;
}

// 检查是否接收完成
uint8_t QR_IsDataReady(void)
{
    return qr_data_ready;
}

// 重置缓冲区，准备接收新数据
void QR_ResetBuffer(void)
{
    qr_index      = 0;
    qr_data_ready = 0;
}

// 获取数据长度
uint16_t QR_GetDataLength(void)
{
    return qr_index;
}

// 获取二维码数据的整数值（仅当内容为纯数字时有效）
int32_t QR_GetIntValue(void)
{
    int32_t value = 0;
    uint16_t i    = 0;

    // 将ASCII码转换为数字
    while (qr_raw_data[i] >= '0' && qr_raw_data[i] <= '9' && i < qr_index) {
        value = value * 10 + (qr_raw_data[i] - '0');
        i++;
    }

    return value;
}

// QR码处理函数
void QR_Process(void)
{
    // 设置显示参数
    LCD_SetAsciiFont(&ASCII_Font24);
    LCD_SetColor(0xFFFF);     // 白色文字
    LCD_SetBackColor(0x0000); // 黑色背景

    LCD_DisplayString(10, 10, "QR Code Scanner");

    // 检查是否有二维码数据就绪
    if (QR_IsDataReady()) {
        // 获取原始数据
        uint8_t *qr_data = QR_GetData();

        // 显示二维码内容
        LCD_DisplayString(10, 50, "Content:");
        LCD_DisplayString(10, 80, (char *)qr_data);

        // 如果是数字内容，显示转换后的整数值
        if (qr_data[0] >= '0' && qr_data[0] <= '9') {
            qr_value = QR_GetIntValue(); // 使用全局变量保存结果
            LCD_DisplayString(10, 120, "Value:");
            LCD_DisplayNumber(100, 120, qr_value, 10);
            if (qr_value != 0) {
                qr_flag = 1;
            }
        }

        // 显示数据长度
        LCD_DisplayString(10, 160, "Length:");
        LCD_DisplayNumber(100, 160, QR_GetDataLength(), 3);

        // 处理完成，重置缓冲区以便接收新数据
        QR_ResetBuffer();
    }
}

/**
 * @brief 获取二维码信息(非阻塞版)
 * @return 1表示获取成功，0表示未获取
 */
uint8_t Get_QR_NonBlock(void)
{
    QR_Process(); // 处理二维码数据
    return qr_flag;
}

/**
 * @brief 启动二维码超时检测
 */
void Start_QR_Detection(void)
{
    // 重置标志
    qr_flag = 0;
    qr_value = 0;
    QR_ResetBuffer();
    // 显示扫描开始
    LCD_DisplayString(10, 200, "QR Scanning...");
    t3_i = 0;
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    while (1) {
        stop();
        if (qr_flag == 1) {
        LCD_DisplayString(10, 120, "Value:");
        LCD_DisplayNumber(100, 120, qr_value, 10);
    }
    else{
        LCD_DisplayString(10, 120, "ValueMiss");
    }
    
        if (qr_flag==1||t3_i>3000) break;
    }
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    t3_i = 0;
}
/**
 * @brief 检查二维码是否已获取或超时
 * @return 0:继续检测 1:检测成功 2:检测超时
 */
uint8_t Check_QR_Status(void)
{
    // 检查是否已获取二维码
    if (qr_flag == 1) {
        LCD_DisplayString(10, 120, "Value:");
        LCD_DisplayNumber(100, 120, qr_value, 10);
        return 1;
    }
    else{
        LCD_DisplayString(10, 120, "ValueMiss");
    }
    return 0; // 继续检测
}
