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

/* 菜单 */
// 全局变量声明
uint8_t Pre_Selection;    // 当前选中的菜单项索引（0-255范围）
uint8_t Traget_Selection; // 目标菜单项索引（0-255范围）
uint8_t X_Pre;            // 当前基准X坐标（0-255范围，控制滑动位置）
uint8_t Speed;            // 动画移动速度（1-255范围，每次调用的像素移动量）
uint8_t Move_Flag;        // 动画状态标志（0=停止，1=进行中）

/**
  * @brief  菜单动画渲染函数
  * @param  无
  * @retval 无
  * @note   实现菜单切换时的滑动动画效果，支持左右双向滑动
  *         使用全局变量控制动画状态
  */
void Menu_Animation(void)
{
    // 清屏准备绘制新帧
    OLED_Clear();
    
    // 在固定位置显示菜单背景框架 (42,10)是坐标，(44,44)是图片尺寸
    OLED_ShowImage(42, 10, 44, 44, Frame);

    // 向右滑动动画处理（当前选中项 < 目标选中项）
    if (Pre_Selection < Traget_Selection)
    {
        // 移动基准位置（向左移动产生右滑视觉效果）
        X_Pre -= Speed;
        
        // 检查是否完成一个项目的滑动距离
        if (X_Pre == 0)
        {
            Pre_Selection++;       // 更新当前选中项索引
            Move_Flag = 0;         // 清除移动标志（表示动画结束）
            X_Pre = 48;            // 重置基准位置（一个菜单项的宽度）
        }
    }
    
    // 向左滑动动画处理（当前选中项 > 目标选中项）
    if (Pre_Selection > Traget_Selection)
    {
        // 移动基准位置（向右移动产生左滑视觉效果）
        X_Pre += Speed;
        
        // 检查是否完成一个项目的滑动距离
        if (X_Pre == 96)
        {
            Pre_Selection--;       // 更新当前选中项索引
            Move_Flag = 0;          // 清除移动标志
            X_Pre = 48;             // 重置基准位置
        }
    }

    // 绘制左侧菜单项（根据位置决定是否显示）
    if (Pre_Selection >= 1)
    {
        // 显示前一个菜单项（位置 = 基准位置 - 48像素）
        OLED_ShowImage(X_Pre - 48, 16, 32, 32, Menu_Graph[Pre_Selection - 1]);
    }
    
    // 绘制更左侧菜单项（如果有）
    if (Pre_Selection >= 2)
    {
        // 显示前两个菜单项（位置 = 基准位置 - 96像素）
        OLED_ShowImage(X_Pre - 96, 16, 32, 32, Menu_Graph[Pre_Selection - 2]);
    }
    
    // 绘制当前选中菜单项（中心位置）
    OLED_ShowImage(X_Pre, 16, 32, 32, Menu_Graph[Pre_Selection]);
    
    // 绘制右侧菜单项
    OLED_ShowImage(X_Pre + 48, 16, 32, 32, Menu_Graph[Pre_Selection + 1]);
    
    // 绘制更右侧菜单项
    OLED_ShowImage(X_Pre + 96, 16, 32, 32, Menu_Graph[Pre_Selection + 2]);
    
    // 更新OLED显示
    OLED_Update();
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

