#include "stm32f10x.h"                  // Device header  

extern uint16_t Timmer_NumCount;

void Timer_Init(void)
{
	//开启定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	//选择内部时钟模式
	TIM_InternalClockConfig(TIM2);
	//时基单元 记数频率 72MHz /（ARR+1）/（PSC+1） 72MHz/10000/7200 =1s
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitSturcture;
	TIM_TimeBaseInitSturcture.TIM_ClockDivision = TIM_CKD_DIV1; //1分频
	TIM_TimeBaseInitSturcture.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInitSturcture.TIM_Period = 2000-1;//ARR重装寄存器
	TIM_TimeBaseInitSturcture.TIM_Prescaler = 7200-1;//PSC预分频寄存器
	TIM_TimeBaseInitSturcture.TIM_RepetitionCounter = 0; //重复计数功能
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitSturcture);
	
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //消除在时基单元初始化之后立即产生的事件中断位
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//中断输出控制,只有指定事件可以触发中断
	
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2,ENABLE);  //使能定时器
}

//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)  //查看TIM2的更新中断标志位
//	{
//		Timmer_NumCount++;
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //手动清除标志位
//	}
//}



