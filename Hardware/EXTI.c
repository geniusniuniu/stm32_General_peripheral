#include "stm32f10x.h"                  // Device header          


uint16_t ItCount = 0;
void EXTi_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //浮空，上拉，下拉输入都可
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//配置AFIO外设
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14); //选择GPIOB的14号引脚作为外部中断线
	
	//初始化EXTI外设
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14; //中断线源
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;  //使能
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	
	EXTI_Init(&EXTI_InitStructure);
	
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//响应优先级
	NVIC_Init(&NVIC_InitStructure);
}

uint16_t Get_ItCount(void)
{
	return ItCount;
}


void EXTI15_10_IRQHandler(void) //中断函数都是无参无返回值的
{
	//先进行中断标志位的判断
	if(EXTI_GetITStatus(EXTI_Line14)==SET)
	{
		
		ItCount++;
		
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}
	
