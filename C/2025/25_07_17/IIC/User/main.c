#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "MyDMA.h"
#include "Serial.h"
#include "Key.h"
#include "LED.h"                   
#include "MyIIC.h"
#include "MPU6050.h"
#include <string.h>




int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	MPU6050_Init();

/* 	MyIIC_Start();
	MyIIC_SendByte(0xD0);		//从机地址加操作 1101 000 0
	uint8_t Ack = MyIIC_ReceiveAck();
	MyIIC_Stop();

	OLED_ShowNum(1, 1, Ack, 3); */

/* 	MPU6050_WriteReg(0x6B, 0x00);		//解除睡眠模式
	MPU6050_WriteReg(0x19, 0x66);		//给0x19地址写入AA
 

	uint8_t ID = MPU6050_ReadReg(0x19);
	OLED_ShowHexNum(1, 1, ID, 2); */

	uint8_t ID;
	int16_t AX, AY, AZ, GX, GY, GZ;
	OLED_ShowString(1, 1 ,"ID:");
	ID = MPU6050_GetID();
	OLED_ShowHexNum(1, 4, ID , 2);
	while (1)
	{
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		OLED_ShowSignedNum(2, 1, AX, 5);
		OLED_ShowSignedNum(3, 1, AY, 5);
		OLED_ShowSignedNum(4, 1, AZ, 5);
		OLED_ShowSignedNum(2, 8, GX, 5);
		OLED_ShowSignedNum(3, 8, GY, 5);
		OLED_ShowSignedNum(4, 8, GZ, 5);


	}
}
