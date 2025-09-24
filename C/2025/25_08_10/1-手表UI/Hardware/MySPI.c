#include "stm32f10x.h"  // STM32F10x系列微控制器标准外设库

/**
  * @brief  设置SPI片选信号(SS)的电平状态
  * @param  BitValue: 电平状态值，0表示低电平，非0表示高电平
  * @note   通过GPIOA的Pin4控制片选信号
  *         当SS为低电平时使能从设备
  */
void MySPI_W_SS(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);
}

/**
  * @brief  初始化SPI1为主机模式
  * @param  无
  * @retval 无
  * @note   配置SPI1工作在全双工主机模式，使用软件NSS控制
  *         引脚分配：
  *         - PA4: SS (片选信号，软件控制)
  *         - PA5: SCK (时钟信号)
  *         - PA6: MISO (主设备输入)
  *         - PA7: MOSI (主设备输出)
  */
void MySPI_Init(void)
{
    /* 开启GPIOA和SPI1的时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* 配置片选引脚SS(PA4)为推挽输出 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;         // 选择PA4引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 高速模式
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* 配置时钟SCK(PA5)和MOSI(PA7)为复用推挽输出 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   // 复用推挽输出(SPI信号控制)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7; // 同时配置PA5(SCK)和PA7(MOSI)
    GPIO_Init(GPIOA, &GPIO_InitStructure);            // 应用配置
    
    /* 配置MISO(PA6)为上拉输入 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     // 上拉输入模式(接收从设备数据)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;         // 选择PA6引脚
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* 配置SPI1工作参数 */
    SPI_InitTypeDef SPI_InitStructure;
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // 全双工模式
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;      // 设置为主机模式
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;  // 8位数据格式
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;         // 时钟极性：空闲状态为低电平
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;       // 时钟相位：数据在第一个边沿采样
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;          // 软件控制NSS(片选信号)
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128; // 波特率预分频值128
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; // 数据传输从最高位(MSB)开始
    SPI_InitStructure.SPI_CRCPolynomial = 7;           // CRC多项式(标准SPI通常不使用)
    SPI_Init(SPI1, &SPI_InitStructure);                // 应用SPI配置

    /* 使能SPI1并初始化片选信号为高电平 */
    SPI_Cmd(SPI1, ENABLE);         // 启动SPI1外设
    MySPI_W_SS(1);                 // 设置片选引脚为高电平(不选中任何从设备)
}

/**
  * @brief  SPI通信开始函数
  * @note   拉低片选信号(SS)，选中从设备
  *         在发送数据前必须调用此函数
  */
void MySPI_Start(void)
{
    MySPI_W_SS(0);    // 片选置低（选中从设备）
}

/**
  * @brief  SPI通信结束函数
  * @note   拉高片选信号(SS)，释放从设备
  *         在数据发送完成后必须调用此函数
  */
void MySPI_Stop(void)
{
    MySPI_W_SS(1);    // 片选置高（释放从设备）
}


/**
  * @brief  通过SPI发送并接收一个字节
  * @param  ByteSend: 要发送的字节数据
  * @retval 接收到的字节数据
  * @note   此函数完成单字节全双工SPI通信
  *         工作流程：
  *         1. 等待发送缓冲区空
  *         2. 写入发送数据（触发传输）
  *         3. 等待接收完成
  *         4. 读取接收数据
  */
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
    /* 等待发送缓冲区为空（TXE=1表示可写入新数据） */
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    
    /* 向数据寄存器写入要发送的字节（启动传输） */
    SPI_I2S_SendData(SPI1, ByteSend);
    
    /* 等待接收完成（RXNE=1表示接收到新数据） */
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    
    /* 读取接收到的字节数据并返回 */
    return SPI_I2S_ReceiveData(SPI1);
}

