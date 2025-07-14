#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "MyDMA.h"
#include "Serial.h"

uint8_t RxData;

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

	while (1)
	{
		if (Serial_GetRxFlag() == 1)
		{
			RxData = Serial_GetRxData();
			Serial_SendByte(RxData);
			OLED_ShowHexNum(1, 8, RxData, 2);
		}
		


	}
}
