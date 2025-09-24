#ifndef __W25Q128_H
#define __W25Q128_H
#include "stm32f10x.h"  // STM32F10x系列微控制器标准外设库

void W25Q128_Init(void);
void W25Q128_WriteEnable(void);
void W25Q128_ReadID(uint8_t *MID, uint16_t *DID);
void W25Q128_WaitBusy(void);
void W25Q128_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count);
void W25Q128_SectorErase(uint32_t Address);
void W25Q128_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count);

#endif
