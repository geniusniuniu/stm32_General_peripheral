#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H
#include <stdio.h>

void Bluetooth_Init(void);
//发送
void Bluetooth_SendByte(uint8_t Byte);
void Bluetooth_SendArray(uint8_t *Array,uint16_t Length);
void Bluetooth_SendString(char *String);
uint32_t Bluetooth_Pow(int x,int y);
void Bluetooth_SendNumber(uint32_t Number,uint8_t Length);
//接收   
uint8_t Bluetooth_GetRxData(void);
uint8_t Bluetooth_GetRxFlag(void); //读取输入标志位后清零

#endif
