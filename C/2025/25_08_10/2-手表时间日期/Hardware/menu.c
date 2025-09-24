#include "stm32f10x.h"                  // Device header
#include "MyRTC.h"
#include "OLED.h"
#include "Key.h"
#include "LED.h"  
#include "SetTime.h"

uint8_t KeyNum;

void Peripheral_Init(void)
{
    MyRTC_Init();
    Key_Init();
    LED_Init();
}

void Show_Clock_UI(void)
{
    MyRTC_ReadTime();
    OLED_Clear();
    OLED_Printf(0, 0, OLED_6X8, "%d-%d-%d", MyRTC_Time[0], MyRTC_Time[1], MyRTC_Time[2]);
    OLED_Printf(16, 16, OLED_12X24, "%02d:%02d:%02d", MyRTC_Time[3], MyRTC_Time[4], MyRTC_Time[5]);
    OLED_ShowString(0, 48, "菜单", OLED_8X16);
    OLED_ShowString(96, 48, "设置", OLED_8X16);
}

int ClkFlag = 1;

int First_Page_Clock(void)
{
    while (1)
    {
        KeyNum = Key_GetNum();

        if (KeyNum == 1)//上一项
        {
            ClkFlag--;
            if (ClkFlag  <= 0)
            {
                ClkFlag = 2;
            }
            
        }
        else if (KeyNum == 2)//下一项
        {
            ClkFlag++;
            if (ClkFlag >= 3)
            {
                ClkFlag = 1;
            }
        }
        else if (KeyNum == 3)//确认
        {
            OLED_Clear();
            OLED_Update();
            return ClkFlag;
        }
        
        switch (ClkFlag)
        {
        case 1:
            OLED_Clear();
            Show_Clock_UI();
            OLED_ReverseArea(0, 48, 32, 16);
            OLED_Update();
            break;

        case 2:
            OLED_Clear();
            Show_Clock_UI();
            OLED_ReverseArea(96, 48, 32, 16);
            OLED_Update();
            break;
        }
    }
    
}


/* 设置界面 */
void Show_SettingPage_UI(void)
{
    OLED_ShowImage(0, 0, 16, 16, Return);
    OLED_ShowString(0, 16, "日期时间设置", OLED_8X16);
}

int SetFlag = 1;

int SettingPage(void)
{
     while (1)
    {
        KeyNum = Key_GetNum();
        uint8_t SetFlag_Temp = 0;

        if (KeyNum == 1)//上一项
        {
            SetFlag--;
            if (SetFlag  <= 0)
            {
                SetFlag = 2;
            }
            
        }
        else if (KeyNum == 2)//下一项
        {
            SetFlag++;
            if (SetFlag >= 3)
            {
                SetFlag = 1;
            }
        }
        else if (KeyNum == 3)//确认
        {
            OLED_Clear();
            OLED_Update();
            SetFlag_Temp = SetFlag;
            
        }

        if (SetFlag_Temp == 1)
        {
            return 0;
        }
        else if (SetFlag_Temp == 2)
        {
            SetTime();
        }

        
        
        switch (SetFlag)
        {
        case 1:
            Show_SettingPage_UI();
            OLED_ReverseArea(0, 0, 16, 16);
            OLED_Update();
            break;

        case 2:
            Show_SettingPage_UI();
            OLED_ReverseArea(0, 16, 96, 16);
            OLED_Update();
            break;
        }
    }
}

