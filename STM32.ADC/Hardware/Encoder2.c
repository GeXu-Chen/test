#include "stm32f10x.h"                  // Device header
void Encoder2_Init(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);    //总时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //若外部模块空闲默认输出高电平，选择上拉
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
//	TIM_InternalClockConfig(TIM3);                         //时基单元所用时钟（内部时钟）
	
	TIM_TimeBaseInitTypeDef TIM_TimBaseInitStructure;
	TIM_TimBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
//	TIM_TimBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//PWM1模式加上向上计数，当CNT<CCR时为有效电平 暨 配置极性为高电平为高时有效所以当CCR变小灯暗
	TIM_TimBaseInitStructure.TIM_Period=65536-1;            //取值在0-65535  ARR
	TIM_TimBaseInitStructure.TIM_Prescaler=1-1;         //取值在0-65535  PSC
	TIM_TimBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimBaseInitStructure);      //配置时基单元
	
	//初始化输入捕获单元
	TIM_ICInitTypeDef TIM_ICinitStructure;
	TIM_ICStructInit(&TIM_ICinitStructure);        //进行初始化，因为有些定义在编码器处用不到
	TIM_ICinitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICinitStructure.TIM_ICFilter = 0xF ;       //滤波器
	TIM_ICinitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising ;     //使用滤波器时不代表极性为上升沿，而是代表高低电平极性不翻转
//	TIM_ICinitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //分频器-触发几次有效一次
//	TIM_ICinitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI ;
TIM_ICInit(TIM3,&TIM_ICinitStructure);  //用此init后直接写入寄存器了，所以结构名不用改可以直接再去配置通道2（Time3通道1，2分别在A6，7）
	
	TIM_ICinitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICinitStructure.TIM_ICFilter = 0xF ;     
	TIM_ICinitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising ;     
	TIM_ICInit(TIM3,&TIM_ICinitStructure);
	
	
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);    //配置编码器模式，此处后两个极性和上面通道极性是一样的，会盖掉上面的输入所以上面通道极性可以不写
//	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Falling); //改一个极性就边方向
	TIM_Cmd(TIM3,ENABLE);
}

int16_t Encoder_Get(void)
{
	int16_t Temp;
	Temp=TIM_GetCounter(TIM3);
	TIM_SetCounter (TIM3,0);
	return Temp;
}
