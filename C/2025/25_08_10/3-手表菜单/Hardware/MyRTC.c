#include "stm32f10x.h"                  // Device header
#include <time.h>


int MyRTC_Time[] = {
    2025,  // 年0
    8,     // 月1
    10,    // 日2
    16,    // 时3
    16,    // 分3
    0     // 秒5
};

void MyRTC_SetTime(void);
/**
  * @brief  初始化RTC（实时时钟）
  * @param  无
  * @retval 无
  * @note   函数执行流程：
  *         1. 使能电源和备份寄存器时钟
  *         2. 允许访问备份区域
  *         3. 启动LSE时钟并等待就绪
  *         4. 配置RTC时钟源为LSE
  *         5. 同步RTC寄存器
  *         6. 设置RTC预分频器和初始计数值
  *         7. 设置初始时间
  */
void MyRTC_Init(void)
{
    /* 1. 使能电源接口和备份寄存器时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    
    /* 2. 允许访问备份区域（RTC和备份寄存器）*/
    PWR_BackupAccessCmd(ENABLE);
    
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)  // 读取备份寄存器DR1的值
    {
        /* --- 首次配置流程 --- */
      /* 3. 启动低速外部时钟（LSE - 32.768kHz）*/
      RCC_LSEConfig(RCC_LSE_ON); // 参数：RCC_LSE_ON 开启LSE振荡器
      /* 等待LSE稳定就绪 */
      while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET); // 阻塞等待直到LSE就绪
      
      /* 4. 配置RTC时钟源 */
      RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); // 参数：RCC_RTCCLKSource_LSE 选择LSE作为RTC时钟源
      RCC_RTCCLKCmd(ENABLE); // 使能RTC时钟
      
      /* 5. 同步RTC寄存器（等待RTC寄存器与APB1时钟同步）*/
      RTC_WaitForSynchro(); // 无参数
      /* 等待最后一次对RTC寄存器的写操作完成 */
      RTC_WaitForLastTask(); // 无参数
      
      /* 6. 配置RTC预分频器 */
      // 目标：1秒中断（32768Hz / 32767+1 = 1Hz）
      RTC_SetPrescaler(32768 - 1); // 参数：预分频值（32767）
      RTC_WaitForLastTask();       // 等待操作完成

      /* 7. 设置初始时间 */
      MyRTC_SetTime();
      /* 设置配置完成标志 */
      BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);  // 在备份寄存器DR1写入标志值0xA5A5
    }
    else  // 非首次配置
    {
        /* 仅进行同步操作 */
        RTC_WaitForSynchro();    // 等待RTC寄存器同步
        RTC_WaitForLastTask();    // 确保RTC状态就绪
    }

}

/**
  * @brief  设置RTC时间
  * @param  无
  * @retval 无
  * @note   函数执行流程：
  *         1. 将用户时间数据转换为tm结构体
  *         2. 使用mktime()转换为UNIX时间戳
  *         3. 将时间戳写入RTC计数器
  *         4. 等待RTC操作完成
  */
void MyRTC_SetTime(void)
{
    time_t time_cnt;      // UNIX时间戳（自1970-01-01 00:00:00起的秒数）
    struct tm time_data;  // 时间结构体
    
    /* 1. 填充tm结构体 */
    time_data.tm_year = MyRTC_Time[0] - 1900;  // 年份偏移（实际年-1900）
    time_data.tm_mon  = MyRTC_Time[1] - 1;     // 月份范围0-11（实际月-1）
    time_data.tm_mday = MyRTC_Time[2];         // 日期1-31
    time_data.tm_hour = MyRTC_Time[3];         // 小时0-23
    time_data.tm_min  = MyRTC_Time[4];         // 分钟0-59
    time_data.tm_sec  = MyRTC_Time[5];         // 秒0-59
    
    // 设置夏令时标志（通常禁用）
    time_data.tm_isdst = 0;  
    
    /* 2. 转换为UNIX时间戳 */
    time_cnt = mktime(&time_data) - 8 * 60 * 60;  // 参数：指向tm结构体的指针
    
    /* 3. 设置RTC计数器值 */
    RTC_SetCounter(time_cnt);       // 参数：32位UNIX时间戳
    
    /* 4. 等待RTC寄存器写入完成 */
    RTC_WaitForLastTask();          // 无参数
}

/**
  * @brief  从RTC读取当前时间并转换为可读格式
  * @param  无
  * @retval 无
  * @note   函数执行流程：
  *         1. 从RTC获取UNIX时间戳
  *         2. 将时间戳转换为tm结构体
  *         3. 从tm结构体提取时间分量
  *         4. 存储到全局时间数组
  */
void MyRTC_ReadTime(void)
{
    time_t time_cnt;      // UNIX时间戳（自1970-01-01 00:00:00起的秒数）
    struct tm time_data;  // 时间结构体
    
    /* 1. 从RTC计数器获取当前UNIX时间戳 */
    time_cnt = RTC_GetCounter() + 8 * 60 * 60;
    
    /* 2. 将时间戳转换为本地时间结构体 */
    time_data = *localtime(&time_cnt);
    /* 3. 提取时间分量并存储到全局数组 */
    MyRTC_Time[0] = time_data.tm_year + 1900;  // 年份（实际年 = tm_year + 1900）
    MyRTC_Time[1] = time_data.tm_mon + 1;      // 月份（实际月 = tm_mon + 1）
    MyRTC_Time[2] = time_data.tm_mday;         // 日期（1-31）
    MyRTC_Time[3] = time_data.tm_hour;         // 小时（0-23）
    MyRTC_Time[4] = time_data.tm_min;          // 分钟（0-59）
    MyRTC_Time[5] = time_data.tm_sec;          // 秒钟（0-59）
}

