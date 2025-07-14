#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "MyDMA.h"
#include "Serial.h"
#include "Key.h"

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
	OLED_ShowString(1, 1, "TxPacket");
	OLED_ShowString(3, 1, "RxPacket");

	Serial_TxPack[0] = 0x01;
	Serial_TxPack[1] = 0x02;
	Serial_TxPack[2] = 0x03;
	Serial_TxPack[3] = 0x04;



	while (1)
	{
		KeyNum = Key_GetNum();
		if (KeyNum == 1)
		{
			Serial_TxPack[0]++;
			Serial_TxPack[1]++;
			Serial_TxPack[2]++;
			Serial_TxPack[3]++;

			Serial_SendPacket();

			OLED_ShowHexNum(2, 1, Serial_TxPack[0], 2);
			OLED_ShowHexNum(2, 4, Serial_TxPack[1], 2);
			OLED_ShowHexNum(2, 7, Serial_TxPack[2], 2);
			OLED_ShowHexNum(2, 10, Serial_TxPack[3], 2);
		}
		
		if (Serial_GetRxFlag() == 1)
		{
			OLED_ShowHexNum(4, 1, Serial_RxPack[0], 2);
			OLED_ShowHexNum(4, 4, Serial_RxPack[1], 2);
			OLED_ShowHexNum(4, 7, Serial_RxPack[2], 2);
			OLED_ShowHexNum(4, 10, Serial_RxPack[3], 2);


		}
		


	}
}
