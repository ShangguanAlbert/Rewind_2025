#ifndef _BSP_QR_H
#define _BSP_QR_H
#include "stm32f10x.h"

void UART4_QRCode_Init(void);
uint8_t *QR_GetData(void);
uint8_t QR_IsDataReady(void);
void QR_ResetBuffer(void);
uint16_t QR_GetDataLength(void);
int32_t QR_GetIntValue(void);
void QR_Process(void);

#endif
