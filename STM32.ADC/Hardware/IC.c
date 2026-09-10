
#include "stm32f10x.h"                  // Device header
void IC_Init(void)
{
	//时钟与实基单元	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);    //总时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;        
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM3);                         //时基单元所用时钟（内部时钟）
	
	TIM_TimeBaseInitTypeDef TIM_TimBaseInitStructure;
	TIM_TimBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//PWM1模式加上向上计数，当CNT<CCR时为有效电平 暨 配置极性为高电平为高时有效所以当CCR变小灯暗
	TIM_TimBaseInitStructure.TIM_Period=65536-1;            //取值在0-65535  ARR
	TIM_TimBaseInitStructure.TIM_Prescaler=72-1;         //取值在0-65535  PSC
	TIM_TimBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimBaseInitStructure);      //配置时基单元
	
	//初始化输入捕获单元
	TIM_ICInitTypeDef TIM_ICinitStructure;
	TIM_ICinitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICinitStructure.TIM_ICFilter = 0xF ;       //滤波器
	TIM_ICinitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising ;
	TIM_ICinitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //分频器-触发几次有效一次
	TIM_ICinitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI ;
	TIM_ICInit(TIM3,&TIM_ICinitStructure);
	
	//主从模式
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);//触发源
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);//配置从模式
	
	TIM_Cmd(TIM3,ENABLE);//启动定时器
}

uint32_t IC_GetFreq(void)
{
	return 1000000 / TIM_GetCapture1(TIM3);
}
