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
  * @brief  设置SPI时钟信号(SCK)的电平状态
  * @param  BitValue: 电平状态值，0表示低电平，非0表示高电平
  * @note   通过GPIOA的Pin5控制时钟信号
  *         时钟上升沿/下降沿触发数据采样
  */
void MySPI_W_SCK(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitValue);
}

/**
  * @brief  设置SPI主机输出数据线(MOSI)的电平状态
  * @param  BitValue: 电平状态值，0表示低电平，非0表示高电平
  * @note   通过GPIOA的Pin7控制主机输出信号
  *         主机通过该引脚向从机发送数据
  */
void MySPI_W_MOSI(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitValue);
}

/**
  * @brief  读取SPI主机输入数据线(MISO)的电平状态
  * @retval uint8_t: 返回读取到的电平状态(0或1)
  * @note   通过GPIOA的Pin6读取从机输入信号
  *         主机通过该引脚接收从机返回的数据
  */
uint8_t MySPI_R_MISO(void)
{
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}

/**
  * @brief  SPI模块初始化函数
  * @note   配置SPI相关的GPIO引脚和初始状态
  *         1. 开启GPIOA时钟
  *         2. 配置SS、MOSI、SCK为推挽输出模式
  *         3. 配置MISO为上拉输入模式
  *         4. 设置初始状态：SS高电平(不选中)，SCK低电平
  */
void MySPI_Init(void)
{
    /* 开启GPIOA的时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    /* 配置SPI输出引脚：SS(PA4)、MOSI(PA7) */
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 配置片选(SS)、主机输出(MOSI)和时钟(SCK)为推挽输出模式
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       // 推挽输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7; // PA4(SS), PA5(SCK), PA7(MOSI)
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      // 高速模式
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* 配置主机输入(MISO)引脚 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          // 上拉输入模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;              // PA6(MISO)
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* 设置初始状态 */
    MySPI_W_SS(1);    // 片选置高（不选中从设备）
    MySPI_W_SCK(0);   // 时钟线置低（空闲状态）
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
  * @brief  SPI全双工数据交换
  * @param  ByteSend: 要发送的字节
  * @retval 接收到的字节
  * @note   使用软件模拟SPI模式0时序（CPOL=0, CPHA=0）：
  *         - 时钟空闲低电平
  *         - 数据在时钟上升沿采样
  *         - MSB先传输
  */
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
    uint8_t ByteReceive = 0x00;

    for (uint8_t i = 0; i < 8; i++)  // 循环8次处理每个位
    {
        /* 发送设置阶段（时钟低电平时设置数据）*/
        MySPI_W_MOSI(ByteSend & (0x80 >> i));  // 从高位(MSB)开始依次发送
        
        /* 时钟上升沿（数据采样时刻）*/
        MySPI_W_SCK(1);  // 产生上升沿
        
        /* 接收数据 */
        if (MySPI_R_MISO() == 1)  // 读取MISO状态
        {
            ByteReceive |= (0x80 >> i);  // 从高位(MSB)开始组装数据
        }
        
        /* 时钟下降沿 */
        MySPI_W_SCK(0);  // 产生下降沿（返回空闲状态）
        
    }
    
    return ByteReceive;
}

/* uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
    uint8_t i = 0;;

    for (i = 0; i < 8; i++)
    {
        MySPI_W_MOSI(ByteSend & (0x80 >> i));
        ByteSend <<= 1;
        MySPI_W_SCK(1);
        if (MySPI_R_MISO() == 1)
        {
            ByteSend |= 0x01;
        }
        MySPI_W_SCK(0);
    }
    

    
    return ByteSend;
} */

