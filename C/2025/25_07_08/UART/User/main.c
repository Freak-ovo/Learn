#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "MYDMA.h"


uint8_t DataA[] = {0x01, 0x02, 0x03, 0x04};
uint8_t DataB[] = {0, 0, 0, 0};

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	AD_Init();		//AD初始化


	/*OLED显示*/

	OLED_ShowString(1, 1, "AD0:");
	OLED_ShowString(2, 1, "AD1:");
	OLED_ShowString(3, 1, "AD2:");
	OLED_ShowString(4, 1, "AD3:");


	while (1)
	{

		OLED_ShowHexNum(1, 5,AD_Value[0], 4);
		OLED_ShowHexNum(2, 5,AD_Value[1], 4);
		OLED_ShowHexNum(3, 5,AD_Value[2], 4);
		OLED_ShowHexNum(4, 5,AD_Value[3], 4);

		Delay_ms(100);

	}
}
