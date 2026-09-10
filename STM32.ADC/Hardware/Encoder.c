//#include "stm32f10x.h"                  // Device header

//int16_t Encoder_Count;

//void Encoder_Init(void)
//{
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	
//GPIO_InitTypeDef GPIO_InitStructure;
//GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
//GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//GPIO_Init(GPIOA,&GPIO_InitStructure);                                    //配置GPIO
//	
//GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);       //配置AFIO
//	
//EXTI_InitTypeDef EXTI_InitStructure;
//EXTI_InitStructure.EXTI_Line=EXTI_Line3;
//EXTI_InitStructure.EXTI_LineCmd=ENABLE;
//EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
//EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
//EXTI_Init(&EXTI_InitStructure);                        //配置EXTI
//	
//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//NVIC_InitTypeDef NVIC_InitStructure1;
//NVIC_InitStructure1.NVIC_IRQChannel=EXTI3_IRQn;
//NVIC_InitStructure1.NVIC_IRQChannelCmd=ENABLE;
//NVIC_InitStructure1.NVIC_IRQChannelPreemptionPriority= 1;
//NVIC_InitStructure1.NVIC_IRQChannelSubPriority= 1;
//NVIC_Init(&NVIC_InitStructure1);       //配置NVIC

//}

//void EXTI3_IRQHandler (void)
//{
//	if(EXTI_GetITStatus(EXTI_Line3)==SET)
//	{
//		if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_3)==0)
//		{
//			 Encoder_Count ++;
//			EXTI_ClearITPendingBit(EXTI_Line3);
//		}
//	}
//}


//int16_t Encoder_Count_Get(void)
//{
//	return Encoder_Count;
//}



