#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "MyDMA.h"
#include "Serial.h"



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
	//Serial_SendByte(0x41);
	//uint8_t MyArray[] = {0x42, 0x43, 0x44, 0x45};
	//Serial_SendArray(MyArray, 4);
	//Serial_SendString("HelloWorld!");
	//Serial_SendNumber(12345, 5);

	//printf("Num=%d\r\n", 666);

	//char String[199];
	//sprintf(String, "Num=%d\r\n", 666);
	//Serial_SendString(String);
	Serial_Printf("Num=%d\r\n", 666);
	while (1)
	{



	}
}
