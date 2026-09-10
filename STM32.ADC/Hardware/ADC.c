#include "stm32f10x.h"                  // Device header

void ADCInit(void)
{
	
RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);  //开启ADC1时钟
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 
	
RCC_ADCCLKConfig(RCC_PCLK2_Div6);  //配置ADCCLK分频器ADCCLK=72Mhz/6=12HZ
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  //模拟输入模式，ADC专用模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);  //规则组输入通道,   通道和序列配置  放在第一个序列上.效果：在规则组菜单列表的第一个位置写入通道0
	
	
	//ADC配置结构
	ADC_InitTypeDef ADC_InitStructure;
  ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;        //选择连续转换还是单次转换
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;    //对齐模式，左对齐或者右对齐
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;     //外部触发转换选择,此处选择内部软件触发所以选none
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;   //独立模式，其他模式皆是双ADC
	ADC_InitStructure.ADC_NbrOfChannel=1;              //选择扫描模式时，总共会用几个通道
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;        //选择扫描模式还是非扫描模式
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_Cmd(ADC1,ENABLE);        //开启ADC电源
	
	
	//对ADC进行校准
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1)==SET);   //返回复位校准状态,通过查寄存器知道1为未完成初始化的状态，完成初始化后变为0即ERESET跳出循环
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1)==SET);
}

uint16_t AD_GetValue(void)
{
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);     //软件触发转换的函数
	while (ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);      //规则组转换完成标志位EOC ,查EOC状态寄存器知道当为0时转换未结束。转换周期固定为12.5而通道采样周期配置为55.5加起来为68个周期，ADCCLK为72MHz/6==12MHz 所以时间为5.6us
	return ADC_GetConversionValue(ADC1) ;
}
