#ifndef _BSP_QR_H
#define _BSP_QR_H
#include "stm32f10x.h"

extern int32_t qr_value;  // 二维码的整数值
extern uint8_t qr_flag ; 

void UART4_QRCode_Init(void);
uint8_t *QR_GetData(void);
uint8_t QR_IsDataReady(void);
void QR_ResetBuffer(void);
uint16_t QR_GetDataLength(void);
int32_t QR_GetIntValue(void);
void QR_Process(void);
uint8_t Get_QR_NonBlock(void);
void Start_QR_Detection(void);
uint8_t Check_QR_Status(void);
void Check_QR_Again(void);
#endif
