#include "stm32f10x.h"  // STM32F10x系列微控制器标准外设库
#include "Delay.h"       // 延时函数库

/*** 
 * @file    AD.c
 * @brief   ADC(模数转换器)驱动模块
 * @details 实现STM32F10x系列ADC1模块的初始化和数据采集功能
 *          支持4通道ADC采集(PA0-PA3)，使用DMA传输转换结果
 *          提供单次采集和均值滤波两种数据获取方式
 * 
 * 特性：
 *  - 12位分辨率ADC
 *  - 4通道连续扫描转换(PA0-PA3)
 *  - DMA自动传输转换结果
 *  - 软件触发转换
 *  - 均值滤波算法减少噪声
 */

// ADC转换值存储数组(4通道)
uint16_t AD_Value[4];

/**
  * @brief  ADC初始化函数
  * @param  无
  * @retval 无
  * @note   初始化ADC1和DMA1通道1，配置如下：
  *         - 时钟：ADC时钟12MHz (PCLK2/6)
  *         - 引脚：PA0-PA3 (ADC通道0-3)
  *         - 模式：独立模式，扫描模式，连续转换
  *         - 采样时间：239.5周期(约20us@12MHz)
  *         - DMA：半字传输，内存地址递增
  */
void AD_Init(void) {
    // 1. 开启外设时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);  // 使能ADC1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能GPIOA时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);    // 使能DMA1时钟
    
    // 2. 配置ADC时钟（PCLK2的6分频）
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);  // 72MHz/6=12MHz（ADC最大时钟14MHz）

    // 3. 配置GPIO为模拟输入模式
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;      // 模拟输入模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // 速度设置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3; // PA0-PA3
    GPIO_Init(GPIOA, &GPIO_InitStructure);             // 应用配置

    // 4. 配置ADC通道参数（4通道）
    // 通道0 (PA0) - 序列1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
    // 通道1 (PA1) - 序列2
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5);
    // 通道2 (PA2) - 序列3
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5);
    // 通道3 (PA3) - 序列4
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5);

    // 5. 初始化ADC基本参数
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;           // 独立模式
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;       // 数据右对齐
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 软件触发
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;          // 单次转换模式
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;                 // 扫描模式(多通道)
    ADC_InitStructure.ADC_NbrOfChannel = 4;                      // 4个转换通道
    ADC_Init(ADC1, &ADC_InitStructure);                          // 应用配置

    // 6. 配置DMA参数
    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_BufferSize = 4;                        // 传输4个数据
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;           // 外设为数据源
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                 // 禁用内存到内存
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;   // 内存目标地址
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; // 16位数据
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;      // 内存地址递增
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                // 普通模式(单次传输)
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR; // 外设地址(ADC数据寄存器)
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 16位数据
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // 外设地址固定
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;        // 中优先级
    
    // 应用DMA配置并启用
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel1, ENABLE);             // 使能DMA通道
    ADC_DMACmd(ADC1, ENABLE);                   // 使能ADC的DMA请求

    // 7. 启动ADC并校准
    ADC_Cmd(ADC1, ENABLE);                      // 使能ADC1
    
    // ADC校准流程
    ADC_ResetCalibration(ADC1);                 // 复位校准寄存器
    while (ADC_GetResetCalibrationStatus(ADC1)); // 等待复位完成
    ADC_StartCalibration(ADC1);                 // 开始校准
    while (ADC_GetCalibrationStatus(ADC1));      // 等待校准完成

    ADC_SoftwareStartConvCmd(ADC1, ENABLE); 
}


