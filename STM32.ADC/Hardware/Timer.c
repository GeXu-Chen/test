#include "stm32f10x.h"                  // Device header
#include "Encoder.h"
int16_t Num;

void Timer_Init(void)
{	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);    //总时钟
	
	TIM_InternalClockConfig(TIM2);                         //时基单元所用时钟（内部时钟）
	
	TIM_TimeBaseInitTypeDef TIM_TimBaseInitStructure;
	TIM_TimBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimBaseInitStructure.TIM_Period=10000-1;           //取值在0-65535
	TIM_TimBaseInitStructure.TIM_Prescaler=7200-1;         //取值在0-65535
	TIM_TimBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimBaseInitStructure);      //配置时基单元
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);                   //给预分频写值后为了让他起作用就先update了一次，而更新伴随中断使得一开始Num就从1开始
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);               //使能（选择）更新中断（开启了更新中断到NVIC的通路）
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);                        //配置NVIC
	
	TIM_Cmd(TIM2,ENABLE);                                  //使能计数器
}

void TIM2_IRQHandler(void)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
{
	if (TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)           //获取更新中断标志位状态
	{
		Num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);            //清除更新中断标志位状态
	}
}

//int16_t Get_Num(void)
//{
//return Num;	
//}

