#include "stm32f10x.h"                  // Device header
#include <stdio.h>

uint8_t Serial1_TxPacket[4];
uint8_t Serial1_RxPacket[4];
uint8_t Serial1_RxFlag;


void Serial1_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//USART_DeInit(USART1);//串口复位 

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);
	
	//RXNE标志位置1，向NVIC申请中断
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//开启RXNE位到NVIC中断配置
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; //中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	USART_Cmd(USART1,ENABLE);
}

void Serial1_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	// USART_FLAG_TXE ==0 数据还没有被移位寄存器转移
	// USART_FLAG_TXE ==1 数据已经被移位寄存器转移
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET); //等待数据转移
}

void Serial1_SendArray(uint8_t *Array,uint16_t Length)
{
	uint16_t i;
	for(i = 0;i < Length;i ++)
		Serial1_SendByte(Array[i]);
}

void Serial1_SendString(char *String)
{
	uint16_t i;
	for(i = 0;String[i] != '0'; i ++)
		Serial1_SendByte(String[i]);
}

uint32_t Pow(int x,int y)
{
	while(y --)
	{
		x *= x;
	}
	return x;
}

void Serial1_SendNumber(uint32_t Number,uint8_t Length)
{
	uint16_t i;
	for(i = 0;i < Length;i ++)
	{
		Serial1_SendByte(Number / Pow(10,Length - i - 1) % 10 + '0');
	}
}

int fputc(int ch,FILE*f)  //printf函数重定向
{
	Serial1_SendByte(ch);
	return ch;
}

uint8_t Serial1_GetRxFlag(void) //读取输入标志位后清零
{
	if(Serial1_RxFlag == 1)
	{
		Serial1_RxFlag = 0;
		return 1;
	}	
	return 0;
}

void Serial1_SendPacket(void)
{
	Serial1_SendByte(0XFF);
	Serial1_SendArray(Serial1_TxPacket,4);
	Serial1_SendByte(0XFE);
}


void USART1_IRQHandler(void)  
{
	static uint8_t RxState = 0;
	static uint8_t DataBitNum = 0;
	
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE))
	{
		uint8_t RxData = USART_ReceiveData(USART1);
		if(RxState == 0)
		{
			if(RxData == 0XFF)
				RxData = 1;
		}
		else if(RxState == 1)
		{
			if(DataBitNum<=4)
				Serial1_TxPacket[DataBitNum ++] =  RxData;
			else
			{
				RxState = 2;
				DataBitNum = 0;
			}
		}
		else if(RxState == 2)
		{
			if(RxData == 0XFE)
			{
				RxState = 0;
				Serial1_RxFlag = 1; 
			}
		}
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}
