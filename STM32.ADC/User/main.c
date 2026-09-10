#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"
#include "Timer.h"
#include "Encoder2.h"
#include "ADC.h"

uint16_t ADValue;

int main (void)
{
ADCInit();
IC_Init();
OLED_Init();
PWM_Init();
Encoder2_Init();
	
	OLED_ShowString(1,1,"ADValue:");
	
PWM_SetOrescaler(720-1);
PWM_SetCompare1(50);
	
while(1)
{
	ADValue=AD_GetValue ();
	OLED_ShowNum(1,9,ADValue,4);
	Delay_ms(500);
}
}	
