#ifndef __MYRTC_H
#define __MYRTC_H
#include "stm32f10x.h"                  // Device header


extern int MyRTC_Time[];

void MyRTC_Init(void);
void MyRTC_SetTime(void);
void MyRTC_ReadTime(void);

#endif
