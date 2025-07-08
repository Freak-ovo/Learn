#include "stm32f10x.h"  // 引入STM32F10x系列微控制器标准外设库
#include "Delay.h"
/***
 * 本代码实现 STM32F10x 系列微控制器的 ADC1 模块初始化和模拟信号采集功能，
 * 用于读取 PA0 引脚（ADC 通道0） 的模拟电压值并转换为 12位数字量（0-4095）。
 * 
 * 
 * 
 * 
 */
// ADC初始化函数
void AD_Init(void) {
    // 1. 开启外设时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);  // 使能ADC1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能GPIOA时钟

    // 2. 配置ADC时钟（PCLK2的6分频）
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);  // 72MHz/6=12MHz（ADC最大时钟通常为14MHz）

    // 3. 配置GPIO为模拟输入模式
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;      // 模拟输入模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // 速度设置（对输入模式无实质影响）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;          // 选择PA0引脚
    GPIO_Init(GPIOA, &GPIO_InitStructure);             // 应用配置

    // 4. 配置ADC通道参数
    ADC_RegularChannelConfig(
        ADC1,                   // 选择ADC1
        ADC_Channel_0,          // 通道0（对应PA0）
        1,                      // 规则组转换序列中的排名（第1个转换）
        ADC_SampleTime_239Cycles5 // 采样时间239个周期（适合中低速信号）
    );

    // 5. 初始化ADC基本参数
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;           // 独立模式（非双ADC模式）
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;       // 数据右对齐
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 软件触发转换
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;          // 单次转换模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;                // 非扫描模式（单通道）
    ADC_InitStructure.ADC_NbrOfChannel = 1;                      // 转换通道数量为1
    ADC_Init(ADC1, &ADC_InitStructure);                          // 应用配置

    // 6. 启动ADC并校准
    ADC_Cmd(ADC1, ENABLE);                    // 使能ADC1
    ADC_ResetCalibration(ADC1);               // 复位校准寄存器
    while (ADC_GetResetCalibrationStatus(ADC1) == SET); // 等待复位完成
    ADC_StartCalibration(ADC1);                // 开始校准
    while (ADC_GetCalibrationStatus(ADC1) == SET);      // 等待校准完成
}

// 获取ADC转换值函数
uint16_t AD_GetValue(void) {
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);         // 启动软件转换
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); // 等待转换完成（EOC标志置位）
    return ADC_GetConversionValue(ADC1);            // 返回12位转换结果
}

// 均值滤波算法
#define SAMPLE_TIMES 16  // 采样次数

uint16_t AD_GetValue_Filtered(void) {
    uint32_t sum = 0;
    for(int i = 0; i < SAMPLE_TIMES; i++) {
        sum += AD_GetValue();
        Delay_us(10);  // 采样间隔
    }
    return sum / SAMPLE_TIMES;
}

