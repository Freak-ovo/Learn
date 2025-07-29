#include "stm32f10x.h"  // STM32F10x系列微控制器标准外设库
#include "Delay.h"       // 延时函数库

/* 引脚配置方法 */
#define SCL_PORT    GPIOB
#define SCL_PIN     GPIO_Pin_10

#define IIC_W_SCL(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)(x))
#define IIC_W_SDA(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)(x))




/**
  * @brief  控制I2C时钟线(SCL)电平状态
  * @param  BitValue: 电平设定值
  *         @arg 0: 设置低电平
  *         @arg 1: 设置高电平
  * @retval 无
  * @note   操作后保持电平10μs以满足I2C时序要求
  *         关联GPIO: PB10 (SCL引脚)
  */
void MyIIC_W_SCL(uint8_t BitValue) 
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)BitValue);  // 设置PB10(SCL)引脚电平
    Delay_us(10);  // 保持电平10微秒(确保信号稳定)
}


/**
  * @brief  控制I2C数据线(SDA)电平状态
  * @param  BitValue: 电平设定值
  *         @arg 0: 设置低电平
  *         @arg 1: 设置高电平
  * @retval 无
  * @note   用于主机主动控制SDA输出
  *         关联GPIO: PB11 (SDA引脚)
  *         电平变化后保持10μs确保信号稳定
  */
void MyIIC_W_SDA(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)BitValue);  // 设置PB11(SDA)引脚电平
    Delay_us(10);  // 保持电平10微秒(确保信号稳定)
}

/**
  * @brief  读取I2C数据线(SDA)电平状态
  * @param  无
  * @retval 当前SDA引脚电平状态
  *         @arg 0: 低电平
  *         @arg 1: 高电平
  * @note   用于读取从机应答信号或数据位
  *         读取后延时10μs保持时序同步
  *         调用前需确保SDA引脚配置为输入模式
  */
uint8_t MyIIC_R_SDA(void)
{
    uint8_t BitValue;  // 存储读取结果的变量
    BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);  // 读取PB11(SDA)引脚电平
    Delay_us(10);  // 等待10微秒(同步时序)
    return BitValue;  // 返回读取到的电平值(0或1)
}


/**
  * @brief  初始化I2C通信所需的GPIO引脚
  * @param  无
  * @retval 无
  * @note   配置PB10(SCL)和PB11(SDA)为开漏输出模式，初始化为高电平
  */
void MyIIC_Init(void)
{
    /* 开启时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // 使能GPIOB的时钟（使用APB2总线）
    
    /* GPIO初始化 */
    GPIO_InitTypeDef GPIO_InitStructure;  // 定义GPIO初始化结构体变量
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  // 设置开漏输出模式（支持I2C线与特性）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;  // 选择PB10(SCL)和PB11(SDA)引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // 设置最高输出速度(50MHz)
    GPIO_Init(GPIOB, &GPIO_InitStructure);  // 应用配置到GPIOB端口
    
    /* 设置默认电平 */
    GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);  // 初始化SCL和SDA为高电平（总线空闲状态）
}

/**
  * @brief  生成I2C起始信号
  * @param  无
  * @retval 无
  * @note   I2C起始条件时序：
  *         1. SDA保持高电平
  *         2. SCL拉高
  *         3. SDA在SCL高电平时产生下降沿
  *         4. 最后拉低SCL钳住总线，准备数据传输
  */
void MyIIC_Start(void)
{
    MyIIC_W_SDA(1);  // 确保SDA为高电平
    MyIIC_W_SCL(1);  // SCL拉高
    MyIIC_W_SDA(0);  // 在SCL高电平时拉低SDA（产生起始信号下降沿）
    MyIIC_W_SCL(0);  // 拉低SCL钳住总线，准备后续传输
}

/**
  * @brief  生成I2C停止信号
  * @param  无
  * @retval 无
  * @note   I2C停止条件时序：
  *         1. SDA保持低电平
  *         2. SCL拉高
  *         3. SDA在SCL高电平时产生上升沿
  */
void MyIIC_Stop(void)
{
    MyIIC_W_SDA(0);  // 确保SDA为低电平
    MyIIC_W_SCL(1);  // SCL拉高
    MyIIC_W_SDA(1);  // 在SCL高电平时拉高SDA（产生停止信号上升沿）
}

/**
  * @brief  发送一个字节数据
  * @param  Byte: 要发送的8位数据
  * @retval 无
  * @note   发送流程：
  *         1. 从高位(MSB)到低位(LSB)依次发送
  *         2. 每bit操作时序：
  *            - 设置SDA电平
  *            - 拉高SCL（数据采样）
  *            - 拉低SCL（准备下一位）
  */
void MyIIC_SendByte(uint8_t Byte)
{
    for (uint8_t i = 0; i < 8; i++)  // 循环发送8个bit
    {
        // 提取当前bit (从最高位开始)
        MyIIC_W_SDA(Byte & (0x80 >> i));  
        // 时钟上升沿（从机采样数据）
        MyIIC_W_SCL(1);
        // 时钟下降沿（准备下一位）
        MyIIC_W_SCL(0);
    }
}

/**
  * @brief  接收一个字节数据
  * @param  无
  * @retval 接收到的8位数据
  * @note   接收流程：
  *         1. 释放SDA线（设置为高电平）
  *         2. 从高位(MSB)到低位(LSB)依次接收
  *         3. 每bit操作时序：
  *            - 拉高SCL（读取数据）
  *            - 读取SDA状态
  *            - 拉低SCL（准备下一位）
  */
uint8_t MyIIC_ReceiveByte(void)
{
    uint8_t Byte = 0x00;
    MyIIC_W_SDA(1);  // 释放SDA线（设置为输入模式）
    
    for (uint8_t i = 0; i < 8; i++)  // 循环接收8个bit
    {
        MyIIC_W_SCL(1);  // 时钟上升沿（数据有效）
        // 读取当前bit值
        if (MyIIC_R_SDA() == 1)  
        {
            Byte |= (0x80 >> i);  // 设置对应位
        }
        MyIIC_W_SCL(0);  // 时钟下降沿（准备下一位）
    }
    return Byte;
}

/**
  * @brief  发送应答信号
  * @param  AckBit: 应答类型
  *         @arg 0: 发送ACK(应答)
  *         @arg 1: 发送NACK(非应答)
  * @retval 无
  * @note   应答时序：
  *         1. 主机设置SDA电平
  *         2. 产生一个时钟脉冲
  *         3. 从机在SCL高电平时读取应答
  */
void MyIIC_SendAck(uint8_t AckBit)
{
    MyIIC_W_SDA(AckBit);  // 设置应答电平 (0:ACK, 1:NACK)
    MyIIC_W_SCL(1);       // 时钟上升沿（从机读取应答）
    MyIIC_W_SCL(0);       // 时钟下降沿（结束应答周期）
}

/**
  * @brief  接收应答信号
  * @param  无
  * @retval 应答状态
  *         @arg 0: 收到ACK(从机应答)
  *         @arg 1: 收到NACK(从机未应答)
  * @note   应答检测时序：
  *         1. 主机释放SDA线
  *         2. 产生时钟脉冲
  *         3. 在SCL高电平时读取SDA状态
  */
uint8_t MyIIC_ReceiveAck(void)
{
    uint8_t AckBit = 0;
    MyIIC_W_SDA(1);      // 释放SDA线（设置为输入）
    
    MyIIC_W_SCL(1);      // 时钟上升沿
    AckBit = MyIIC_R_SDA();  // 读取应答信号 (0:ACK, 1:NACK)
    MyIIC_W_SCL(0);      // 时钟下降沿
    
    return AckBit;
}

