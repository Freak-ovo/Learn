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
#include <string.h>

uint8_t MID;
uint16_t DID;

uint8_t ArrayWrite[] = { 0xA1, 0xB2, 0xC3, 0xD4};
uint8_t ArrayRead[4];

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	W25Q128_Init();

	OLED_ShowString(1, 1, "MID:   DID:");
	OLED_ShowString(2, 1, "W:");
	OLED_ShowString(3, 1, "R:");

	W25Q128_ReadID(&MID, &DID);

	OLED_ShowHexNum(1, 5, MID, 2);
	OLED_ShowHexNum(1, 12, DID, 4);

	W25Q128_SectorErase(0x000000);
/* 	W25Q128_PageProgram(0x000000, ArrayWrite, 4); */

	W25Q128_ReadData(0x000000, ArrayRead, 4);

	OLED_ShowHexNum(2, 3, ArrayWrite[0], 2);
	OLED_ShowHexNum(2, 6, ArrayWrite[1], 2);
	OLED_ShowHexNum(2, 9, ArrayWrite[2], 2);
	OLED_ShowHexNum(2, 12, ArrayWrite[3], 2);

	OLED_ShowHexNum(3, 3, ArrayRead[0], 2);
	OLED_ShowHexNum(3, 6, ArrayRead[1], 2);
	OLED_ShowHexNum(3, 9, ArrayRead[2], 2);
	OLED_ShowHexNum(3, 12, ArrayRead[3], 2);

	while (1)
	{



	}
}

