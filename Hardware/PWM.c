#include "stm32f10x.h"                  // Device header          

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//TIM2输出比较通道1默认复用PA0引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure); 
	
	TIM_InternalClockConfig(TIM2);
	//生成一个周期为10ms的PWM波，占空比为50%
	TIM_TimeBaseInitTypeDef TimeBaseInitStructure;
	TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBaseInitStructure.TIM_Period = 100-1; //ARR
	TimeBaseInitStructure.TIM_Prescaler = 7200-1; //PSC
	TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TimeBaseInitStructure);
	
	//配置输出比较   占空比：CCR/（ARR+1）
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);//需要先初始化再使用
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;	
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性（高电平有效
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; //使能开关
	TIM_OCInitStruct.TIM_Pulse = 50; //CCR捕获比较寄存器的值	
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);
	
	TIM_Cmd(TIM2,ENABLE);
	
}

void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare);
}


void PWM_SetPrescale(uint16_t Prescale)
{
	TIM_PrescalerConfig(TIM2,Prescale,TIM_PSCReloadMode_Immediate);
}
