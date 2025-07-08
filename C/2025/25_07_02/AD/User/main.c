#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"


uint16_t ADValue;
uint16_t ADValueFiltered;
float Voltage;

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	AD_Init();		//AD初始化

	/*OLED显示*/
    OLED_ShowString(1, 1, "ADValue:");
    OLED_ShowString(2, 1, "ADfiler:");
    OLED_ShowString(3, 1, "Voltage:");


	
	while (1)
	{
		ADValue = AD_GetValue();
		ADValueFiltered = AD_GetValue_Filtered();
		Voltage = (float) AD_GetValue() / 4095 * 3.3;


		OLED_ShowNum(1, 9, ADValue, 4);

		OLED_ShowNum(2, 9, ADValueFiltered, 4);
		OLED_ShowNum(3, 9, Voltage, 1);
		OLED_ShowNum(3, 11, (uint16_t)(Voltage * 100) % 100, 2);

        Delay_ms(100);

	}
}
