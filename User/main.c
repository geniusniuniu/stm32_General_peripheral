#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"
#include "math.h"
//#include "Led.h"
//#include "Keys.h"
//#include "EXTi.h"
//#include "Encoder.h"  //外部中断编码器
//#include "Timer.h"
//#include "PWM.h"
//#include "InputCompare.h"
//#include "Tim_Encoder.h"  //定时器编码器模式
#include "W25Qxx.h"
#include "AD.h"
#include "Serial.h"
#include "MPU6050.h"
#include "MyRTC.h"
#include "Bluetooth.h"
/
extern MyRTC_TimeStructTypeDef MyRTC_TimeStruct;

void Misc_Init(void)
{
	OLED_Init();
//	Led_Init();
//	Key_Init();
//	EXTi_Init();
//	Encoder_Init();
//	Timer_Init();
//	PWM_Init();
//	IC_Init();
//	TimEncoder_Init();
//	PWM_SetCompare1(Pulse1);
//	PWM_SetPrescale(Prescale1);
//	AD_Init();
	Serial1_Init();
//	MPU6050_Init();
//	W25Qxx_Init();
//	MyRTC_Init();
//	Bluetooth_Init();
}
void Show_ADTest()
{
	int16_t ADValue;
	OLED_ShowString(1,1,"ADValue:");
	ADValue = AD_GetValue();
	OLED_ShowNum(1,9,ADValue,4);
}
void Show_MPUTest(void)
{
	int16_t AX, AY, AZ, GX, GY, GZ;
	uint8_t ID;
	ID = MPU6050_ReadID();
	OLED_ShowHexNum(1,5,ID,4);
	MPU6050_ReadData(&AX, &AY, &AZ, &GX, &GY, &GZ);
	OLED_ShowSignedNum(2, 1, AX, 5);
	OLED_ShowSignedNum(3, 1, AY, 5);
	OLED_ShowSignedNum(4, 1, AZ, 5);
	OLED_ShowSignedNum(2, 9, GX, 5);
	OLED_ShowSignedNum(3, 9, GY, 5);
	OLED_ShowSignedNum(4, 9, GZ, 5);	
}



void Show_W25QxxTest(void)
{
	uint8_t MID;
	uint16_t DID;
	uint8_t ArrayWrite[4]= {0xAB,0xBC,0xCD,0xDF};
	uint8_t ArrayRead[8];
	W25Qxx_ReadID(&MID,&DID);
	OLED_ShowString(1,1,"MID");
	OLED_ShowString(1,7,"DID");
	OLED_ShowHexNum(1,1,MID,2);
	OLED_ShowHexNum(1,11,DID,4);
	
	OLED_ShowString(2,1,"W");
	OLED_ShowString(3,1,"R");

	W25Qxx_SectorErase4KB(0x000000);
	W25Qxx_PageProgram(0x000000, ArrayWrite, 4);
	
	W25Qxx_ReadData(0x000000, ArrayRead, 4);
	
	OLED_ShowHexNum(2, 3, ArrayWrite[0], 2);
	OLED_ShowHexNum(2, 6, ArrayWrite[1], 2);
	OLED_ShowHexNum(2, 9, ArrayWrite[2], 2);
	OLED_ShowHexNum(2, 12, ArrayWrite[3], 2);
	
	OLED_ShowHexNum(3, 3, ArrayRead[0], 2);
	OLED_ShowHexNum(3, 6, ArrayRead[1], 2);
	OLED_ShowHexNum(3, 9, ArrayRead[2], 2);
	OLED_ShowHexNum(3, 12, ArrayRead[3], 2);
	OLED_ShowHexNum(4, 3, ArrayRead[4], 2);
	OLED_ShowHexNum(4, 6, ArrayRead[5], 2);
}

void Show_RTCTest(void)
{
	MyRTC_ReadTime();
	OLED_ShowNum(1,6,MyRTC_TimeStruct.Year,4);
	OLED_ShowNum(1,11,MyRTC_TimeStruct.Month,2);
	OLED_ShowNum(1,14,MyRTC_TimeStruct.Day,2);
	OLED_ShowNum(2,6,MyRTC_TimeStruct.Hour,2);
	OLED_ShowNum(2,9,MyRTC_TimeStruct.Minute,2);
	OLED_ShowNum(2,12,MyRTC_TimeStruct.Second,2);
}

void Bluetooth_Test(void)
{
	printf("A");
}
uint8_t RxData;
int main(void) 
{
	Misc_Init();
	//Bluetooth_SendString("B");
    while (1)
    {
    }
}



//void TIM2_IRQHandler(void)  //0.2s进入一次中断
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)  //查看TIM2的更新中断标志位
//	{
//		//speed = TimEncoder_Get();
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //手动清除标志位
//	}
//}
