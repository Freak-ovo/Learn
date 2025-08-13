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

uint8_t KeyNum;

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Key_Init();
	
	MyRTC_Init();

	OLED_ShowString(1, 1, "Data:XXXX-XX-XX");
	OLED_ShowString(2, 1, "Time:XX:XX:XX");
	OLED_ShowString(3, 1, "CNT:");

	while (1)
	{
		MyRTC_ReadTime();
		OLED_ShowNum(1, 6, MyRTC_Time[0], 4);
		OLED_ShowNum(1, 11, MyRTC_Time[1], 2);
		OLED_ShowNum(1, 14, MyRTC_Time[2], 2);
		OLED_ShowNum(2, 6, MyRTC_Time[3], 2);
		OLED_ShowNum(2, 9, MyRTC_Time[4], 2);
		OLED_ShowNum(2, 12, MyRTC_Time[5], 2);

		OLED_ShowNum(3, 6, RTC_GetCounter(), 10);




	}
}

