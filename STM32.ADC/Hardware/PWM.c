#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);    //总时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;        //应用了PA0的复用功能，所以用复用推挽输出让引脚连上定时器的CH1通道
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);                         //时基单元所用时钟（内部时钟）
	
	TIM_TimeBaseInitTypeDef TIM_TimBaseInitStructure;
	TIM_TimBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//PWM1模式加上向上计数，当CNT<CCR时为有效电平 暨 配置极性为高电平为高时有效所以当CCR变小灯暗
	TIM_TimBaseInitStructure.TIM_Period=100-1;            //取值在0-65535  ARR
	TIM_TimBaseInitStructure.TIM_Prescaler=72-1;         //取值在0-65535  PSC
	TIM_TimBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimBaseInitStructure);      //配置时基单元
	
	TIM_OCInitTypeDef TIM_OCInitStructure;                 //配置输出比较通道
	TIM_OCStructInit(&TIM_OCInitStructure);                //配置通用定时器时有些高级定时器的参数没初始化，为避免问题用此函数先全部初始化该结构体再做修改
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;         
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;     //高极性为高电平时为有效电平(连电路时等高电平与Pino相连，这样用起来更顺一点
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;                      //CCR  是得频率为1K，占空比50%，分辨率1%
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);               //选择通道CH1                   
	
	TIM_Cmd(TIM2,ENABLE);                                  //使能计数器
	
}

void PWM_SetCompare1(uint16_t Compare)                  //改变CCR的值
{
	TIM_SetCompare1(TIM2,Compare);
}

void PWM_SetOrescaler(uint16_t Prescaler)
{
		TIM_PrescalerConfig(TIM2,Prescaler,TIM_PSCReloadMode_Immediate);
}
