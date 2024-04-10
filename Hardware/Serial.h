#ifndef __Serial1_H
#define __Serial1_H
#include <stdio.h>

extern uint8_t Serial1_TxPacket[];
extern uint8_t Serial1_RxPacket[];

void Serial1_Init(void);
//发送
void Serial1_SendByte(uint8_t Byte);
void Serial1_SendArray(uint8_t *Array,uint16_t Length);
void Serial1_SendString(char *String);
uint32_t Pow(int x,int y);
void Serial1_SendNumber(uint32_t Number,uint8_t Length);
//接收  
uint8_t Serial1_GetRxData(void);
uint8_t Serial1_GetRxFlag(void); //读取输入标志位后清零

#endif
