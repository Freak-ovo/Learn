#include "stm32f10x.h"                  // Device header
#include "MyRTC.h"
#include "OLED.h"
#include "Key.h"
#include "LED.h"  
#include "SetTime.h"
#include "Menu.h"
#include "Delay.h"

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

/* 菜单 */
uint8_t Pre_Selection;//上次选择的选项
uint8_t Traget_Selection;//目标选项
uint8_t X_Pre = 48;//上次选项x的坐标
uint8_t Speed = 4;//速度
uint8_t Move_Flag;//开始移动的标志位，1表示开始移动，0表示停止移动

void Menu_Animation(void)
{
    OLED_Clear();
    OLED_ShowImage(42, 10, 44, 44,Frame);

    if (Pre_Selection < Traget_Selection)
    {
        X_Pre -= Speed;
        if (X_Pre == 0)
        {
            Pre_Selection++;
            Move_Flag = 0;
            X_Pre = 48;
        }
        
    }
    if (Pre_Selection > Traget_Selection)
    {
        X_Pre += Speed;
        if (X_Pre == 96)
        {
            Pre_Selection--;
            Move_Flag = 0;
            X_Pre = 48;
        }
        
    }
    if (Pre_Selection >= 1)
    {
        OLED_ShowImage(X_Pre - 48, 16, 32, 32,Menu_Graph[Pre_Selection - 1]);
    }
    if (Pre_Selection >= 2)
    {
        OLED_ShowImage(X_Pre - 96, 16, 32, 32,Menu_Graph[Pre_Selection - 2]);
    }
    OLED_ShowImage(X_Pre, 16, 32, 32,Menu_Graph[Pre_Selection]);
    OLED_ShowImage(X_Pre + 48, 16, 32, 32,Menu_Graph[Pre_Selection + 1]);
    OLED_ShowImage(X_Pre + 96, 16, 32, 32,Menu_Graph[Pre_Selection + 2]);
    
    OLED_Update();

    
}

void Set_Selection(uint8_t Move_Flag, uint8_t New_Pre_Selection, uint8_t New_Traget_Selection)
{
    if (Move_Flag == 1)
    {
        Pre_Selection = New_Pre_Selection;
        Traget_Selection = New_Traget_Selection;

    }
    Menu_Animation();
    
}

void MenuToFunction(void)
{

    for (uint8_t i = 0; i < 6; i++)
    {
        OLED_Clear();
        if (Pre_Selection >= 1)
        {
            OLED_ShowImage(X_Pre - 48, 16 + 8 * i, 32, 32,Menu_Graph[Pre_Selection - 1]);
        }
        OLED_ShowImage(X_Pre, 16 + 8 * i, 32, 32,Menu_Graph[Pre_Selection]);
        OLED_ShowImage(X_Pre + 48, 16 + 8 * i, 32, 32,Menu_Graph[Pre_Selection + 1]);
        
        OLED_Update();
    }
    

}

uint8_t Menu_Flag = 1;

int Menu(void)
{
    Move_Flag = 1;
    uint8_t Dircect_Flag = 2;//置1移动到上一项， 置2移动到下一项
    while (1)
    {
        KeyNum = Key_GetNum();
        uint8_t Menu_Flag_Temp = 0;

        if (KeyNum == 1)//上一项
        {
            Dircect_Flag = 1;
            Move_Flag = 1;
            Menu_Flag--;
            if (Menu_Flag  <= 0)
            {
                Menu_Flag = 7;
            }
            
        }
        else if (KeyNum == 2)//下一项
        {
            Dircect_Flag = 2;
            Move_Flag = 1;
            Menu_Flag++;
            if (Menu_Flag >= 8)
            {
                Menu_Flag = 1;
            }
        }
        else if (KeyNum == 3)//确认
        {
            OLED_Clear();
            OLED_Update();
            Menu_Flag_Temp = Menu_Flag;
            
        }

        if (Menu_Flag_Temp == 1)
        {
            return 0;
        }
        else if (Menu_Flag_Temp == 2)
        {
            MenuToFunction();
            StopWatch();
        }
        else if (Menu_Flag_Temp == 3)
        {
            
        }
        else if (Menu_Flag_Temp == 4)
        {

        }
        else if (Menu_Flag_Temp == 5)
        {
            
        }
        else if (Menu_Flag_Temp == 6)
        {
            
        }
        else if (Menu_Flag_Temp == 7)
        {
            
        }
        
      
        if (Menu_Flag == 1)
        {
            if (Dircect_Flag == 1)
            {
                Set_Selection(Move_Flag, 1, 0);
            }
            else if (Dircect_Flag == 2)
            {
                Set_Selection(Move_Flag, 0, 0);
            }
        }
        else
        {
            if (Dircect_Flag == 1)
            {
                Set_Selection(Move_Flag, Menu_Flag, Menu_Flag - 1);
            }
            else if (Dircect_Flag == 2)
            {
                Set_Selection(Move_Flag, Menu_Flag - 2, Menu_Flag - 1);
            }
        }
        
    }
}




/* 秒表 */


uint8_t hour = 0, min = 0, sec = 0;
void Show_StopWatch_UI(void)
{
    OLED_ShowImage(0, 0, 16, 16, Return);
    OLED_Printf(32, 20, OLED_8X16, "%02d:%02d:%02d", hour, min, sec);
    OLED_ShowString(8, 44, "开始", OLED_8X16);
    OLED_ShowString(48, 44, "停止", OLED_8X16);
    OLED_ShowString(88, 44, "清除", OLED_8X16);

}

uint8_t Start_Timing_Flag;      //1开始 0停止
void StopWatch_Tick(void)
{
    static uint16_t Count;
    Count++;
    if (Count >= 1000)
    {
        Count = 0;
        if (Start_Timing_Flag == 1)
        {
            sec++;
            if (sec >= 60)
            {
                sec = 0;
                min++;
                if (min >= 60)
                {
                    min = 0;
                    hour++;
                    if (hour > 99)
                    {
                        hour = 0;
                    }
                    
                }
                
            }
            
        }
    }
    
    
    
}


uint8_t StopWatch_Flag = 1;

int StopWatch(void)
{
    while (1)
    {
        KeyNum = Key_GetNum();
        uint8_t StopWatch_Flag_Temp = 0;

        if (KeyNum == 1)//上一项
        {
            StopWatch_Flag--;
            if (StopWatch_Flag  <= 0)
            {
                StopWatch_Flag = 4;
            }
            
        }
        else if (KeyNum == 2)//下一项
        {
            StopWatch_Flag++;
            if (StopWatch_Flag >= 5)
            {
                StopWatch_Flag = 1;
            }
        }
        else if (KeyNum == 3)//确认
        {
            OLED_Clear();
            OLED_Update();
            StopWatch_Flag_Temp = StopWatch_Flag;
            
        }

        if (StopWatch_Flag_Temp == 1)
        {
            return 0;
        }
        
        switch (StopWatch_Flag)
        {
        case 1:
            Show_StopWatch_UI();
            OLED_ReverseArea(0, 0, 16, 16);
            OLED_Update();
            break;

        case 2:
            Show_StopWatch_UI();
            Start_Timing_Flag = 1;
            OLED_ReverseArea(8, 44, 32, 16);
            OLED_Update();
            break;

        case 3:
            Show_StopWatch_UI();
            Start_Timing_Flag = 0;
            OLED_ReverseArea(48, 44, 32, 16);
            OLED_Update();
            break;

        case 4:
            Show_StopWatch_UI();
            Start_Timing_Flag = 0;
            hour = min = sec = 0;
            OLED_ReverseArea(88, 44, 32, 16);
            OLED_Update();
            break;
        }
    }
}