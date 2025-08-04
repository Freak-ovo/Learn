#include "stm32f10x.h"  // STM32F10x系列微控制器标准外设库

// 全局变量：存储DMA传输的数据量大小
uint16_t MyDMA_Size;

/**
  * @brief  初始化DMA配置
  * @param  AddrA: 源数据地址 (外设/内存地址)
  * @param  AddrB: 目标数据地址 (内存地址)
  * @param  Size: 要传输的数据量（单位：字节）
  * @retval 无
  * @note   此函数配置DMA1的通道1，用于内存到内存的传输
  *         配置完成后DMA处于禁用状态，需要调用MyDMA_Transfer启动传输
  */
void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t Size)
{
    // 保存传输数据量供后续使用
    MyDMA_Size = Size;

    // 1. 开启DMA1时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    // 2. 初始化DMA结构体参数
    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_BufferSize = Size;             // 传输数据量
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;   // 传输方向：外设为源
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;          // 内存到内存模式
    DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;        // 目标内存地址
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte; // 内存数据宽度：字节
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; // 内存地址自增
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;        // 传输模式：单次传输
    DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;    // 外设/源地址
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 外设数据宽度：字节
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable; // 外设地址自增
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; // DMA通道优先级：中
    
    // 3. 应用配置到DMA1通道1
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    // 4. 初始状态禁用DMA通道（等待传输命令）
    DMA_Cmd(DMA1_Channel1, DISABLE);
}

/**
  * @brief  执行DMA传输
  * @param  无
  * @retval 无
  * @note   此函数执行完整的DMA传输过程：
  *         1. 禁用通道（确保配置更新）
  *         2. 设置传输数据量
  *         3. 启用DMA通道
  *         4. 等待传输完成
  *         5. 清除传输完成标志
  */
void MyDMA_Transfer(void)
{
    // 1. 禁用DMA通道（确保可以安全更新配置）
    DMA_Cmd(DMA1_Channel1, DISABLE);
    
    // 2. 设置要传输的数据量
    DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size);
    
    // 3. 启用DMA通道，开始传输
    DMA_Cmd(DMA1_Channel1, ENABLE);

    // 4. 等待传输完成（阻塞等待）
    while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET) {
        // 空循环等待传输完成标志置位
        // 实际应用中可添加超时检测或中断处理
    }
    
    // 5. 清除传输完成标志
    DMA_ClearFlag(DMA1_FLAG_TC1);
}
