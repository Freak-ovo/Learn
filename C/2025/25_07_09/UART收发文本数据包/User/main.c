#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "MyDMA.h"
#include "Serial.h"
#include "Key.h"
#include "LED.h"
#include <string.h>

uint8_t KeyNum;


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  * @note   初始化串口后，循环发送测试数据
  */

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Serial_Init();
	Key_Init();
	LED_Init();

	OLED_ShowString(1, 1, "TxPacket");
	OLED_ShowString(3, 1, "RxPacket");



	while (1)
	{

		if (Serial_GetRxFlag() == 1)
		{
			
			OLED_ShowString(4, 1, "                ");
			OLED_ShowString(4, 1, Serial_RxPack);

			if (strcmp(Serial_RxPack, "LED_ON") == 0)
			{
				LED1_ON();
				Serial_SendString("LED_ON_OK\r\n");
				OLED_ShowString(2, 1, "                ");
				OLED_ShowString(2, 1, "LED_ON_OK");

			}
			else if (strcmp(Serial_RxPack, "LED_OFF") == 0)
			{
				LED1_OFF();
				Serial_SendString("LED_OFF_OK\r\n");
				OLED_ShowString(2, 1, "                ");
				OLED_ShowString(2, 1, "LED_OFF_OK");
			}
			else
			{
				Serial_SendString("ERROR_COMMAND\r\n");
				OLED_ShowString(2, 1, "                ");
				OLED_ShowString(2, 1, "ERROR_COMMAND");
			}
			
		}

		
	}
}
