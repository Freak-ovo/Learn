#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "MyDMA.h"
#include "Serial.h"
#include "Key.h"
#include "LED.h"                   
#include "MPU6050.h"
#include "W25Q128.h"
#include "MyRTC.h"
#include <string.h>
#include "menu.h"
#include "Timer.h"
#include "SetTime.h"


int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	OLED_Clear();
	Peripheral_Init();
	Timer_Init();
	int ClkFlag1;

	while (1)
	{
		ClkFlag1 = First_Page_Clock();
		if (ClkFlag1 == 1)//菜单
		{
			Menu();
		}
		else if (ClkFlag1 == 2)//设置
		{
			SettingPage();
		}
		
	}
}

 //定时器中断函数，可以复制到使用它的地方
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		Key_Tick();
		StopWatch_Tick(); 
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

