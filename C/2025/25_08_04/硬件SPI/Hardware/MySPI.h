#ifndef __MYSPI_H
#define __MYSPI_H
#include "stm32f10x.h"  // STM32F10x系列微控制器标准外设库

void MySPI_Init(void);
void MySPI_Start(void);
void MySPI_Stop(void);
uint8_t MySPI_SwapByte(uint8_t ByteSend);

#endif
