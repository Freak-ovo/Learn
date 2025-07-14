#include "stm32f10x.h"  // STM32标准外设库头文件
#include <stdio.h>
#include <stdarg.h>

uint8_t Serial_RxData;
uint8_t Serial_RxFlag;
uint8_t Serial_RxPack[4];
uint8_t Serial_TxPack[4];





/**
  * @brief  串口初始化函数
  * @param  无
  * @retval 无
  * @note   初始化USART1，配置为9600波特率、8位数据位、无校验位、1停止位
  */
void Serial_Init(void)
{
    /* 启用USART1和GPIOA的时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);  // 使能USART1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 使能GPIOA时钟

    /* GPIO初始化 - 配置USART1的TX引脚(PA9) */
    GPIO_InitTypeDef GPIO_InitStructure;  // 定义GPIO初始化结构体
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       // 复用推挽输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;             // 选择引脚9 (PA9 - USART1_TX)
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     // 输出速度50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                // 初始化GPIOA

    /* 配置GPIO引脚参数 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       // 上拉输入模式 (用于接收信号)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;          // 选择引脚10 (PA10 - USART1_RX)
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   // 引脚响应速度50MHz (优化信号完整性)
    GPIO_Init(GPIOA, &GPIO_InitStructure);              // 应用配置到GPIOA端口 

    /* USART参数配置 */
    USART_InitTypeDef USART_InitStructure;  // 定义USART初始化结构体
    USART_InitStructure.USART_BaudRate = 9600;                          // 波特率9600bps
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件流控
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;     // 使能发送和接收模式
    USART_InitStructure.USART_Parity = USART_Parity_No;                 // 无奇偶校验
    USART_InitStructure.USART_StopBits = USART_StopBits_1;              // 1位停止位
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;         // 8位数据长度
    USART_Init(USART1, &USART_InitStructure);                           // 初始化USART1

    /* 使能USART1 */
    USART_Cmd(USART1, ENABLE);  // 启动USART1外设

    /* 配置接收中断 */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);           // 使能接收中断（RX Not Empty）

    /* 配置NVIC中断控制器 */
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);          // 设置中断优先级分组
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;        // USART1中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;       // 子优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;          // 使能中断通道
    NVIC_Init(&NVIC_InitStructure);                          // 应用NVIC配置

    /* 使能USART1 */
    USART_Cmd(USART1, ENABLE);                               // 启动USART1外设
}




/**
  * @brief  串口发送单字节数据
  * @param  Byte: 要发送的字节数据
  * @retval 无
  * @note   通过USART1发送一个字节，并等待发送完成
  */
void Serial_SendByte(uint8_t Byte)
{
    /* 将数据写入发送数据寄存器 */
    USART_SendData(USART1, Byte);  // 将字节数据放入发送缓冲区
    
    /* 等待发送完成（TXE标志置位） */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
    {
        // 空循环，等待发送缓冲区空标志(TXE)置位
        // TXE=1表示数据已转移到移位寄存器，可以发送新数据
    }
}

/**
  * @brief  串口发送字节数组
  * @param  Array:  指向要发送的字节数组的指针
  * @param  Length: 要发送的字节数量
  * @retval 无
  * @note   通过USART1连续发送多个字节数据
  *         此函数复用Serial_SendByte()，确保每个字节完整发送后才发送下一个字节
  *         使用阻塞方式发送，适用于小数据量传输
  */
void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
    uint16_t i;  // 循环计数器
    
    // 遍历数组中的每个字节
    for (i = 0; i < Length; i++)
    {
        // 调用Serial_SendByte函数发送当前字节
        // 该函数内部已包含等待发送完成的逻辑
        Serial_SendByte(Array[i]);
    }
}


/**
  * @brief  发送以空字符('\0')结尾的字符串
  * @param  String: 指向要发送的字符串的指针
  * @retval 无
  * @note   此函数遍历字符串直到遇到空终止符('\0')，通过串口发送每个字符
  *         适用于发送C语言风格的空终止字符串
  *         
  */
void Serial_SendString(char *String)
{
    uint8_t i;  // 字符索引计数器
    
    // 遍历字符串中的每个字符，直到遇到空终止符(ASCII 0)
    for (i = 0; String[i] != '\0'; i++)
    {
        // 调用Serial_SendByte发送当前字符
        // 由于char类型与uint8_t兼容，可以直接传递
        Serial_SendByte(String[i]);
    }
}


/**
 * 计算无符号整数X的Y次幂。
 * @param X 底数（无符号32位整数）
 * @param Y 指数（无符号32位整数）
 * @return X的Y次幂的结果（无符号32位整数）
 */
uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;
    // 循环Y次，每次将Result乘以X
    while (Y--)
    {
        Result *= X;
    }
    
    return Result;
}

/**
 * 将无符号整数按指定长度逐位通过串口发送（以ASCII字符形式）。
 * @param Number 要发送的无符号32位整数
 * @param Length 指定发送的数字位数（不足时高位补零，超过时截断高位）
 */
void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
    uint8_t i;
    // 从最高位开始，逐位处理Length位数字
    for (i = 0; i < Length; i++)
    {
        // 计算当前位的数值：Number / 10^(Length-i-1) % 10
        // 转换为ASCII码（数字0~9对应0x30~0x39）后发送
        Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + 0x30);
    }
}

int fputc(int ch, FILE *f)
{
    Serial_SendByte(ch);
    return ch;
}


void Serial_Printf(char *format, ...)
{
    char String[100];            // 1. 创建输出缓冲区
    va_list arg;                 // 2. 声明可变参数列表
    va_start(arg, format);       // 3. 初始化可变参数
    vsprintf(String, format, arg); // 4. 格式化字符串
    va_end(arg);                 // 5. 清理可变参数
    Serial_SendString(String);   // 6. 发送格式化后的字符串
}


/**
  * @brief  检查串口接收标志位
  * @param  无
  * @retval uint8_t 
  *         1: 接收到新数据
  *         0: 未接收到新数据
  * @note   此函数会清除接收标志位
  */
uint8_t Serial_GetRxFlag(void)
{
    if (Serial_RxFlag == 1)       // 检查接收标志位是否置位
    {
        Serial_RxFlag = 0;        // 清除接收标志位
        return 1;                 // 返回接收到新数据
    }
    return 0;                     // 无新数据
}



/**
  * @brief  发送串口数据包
  * @param  无
  * @retval 无
  * @note   发送固定格式的数据包：
  *         起始标志: 0xFF (1字节)
  *         数据内容: Serial_TxPack数组 (4字节)
  *         结束标志: 0xFE (1字节)
  *         总长度: 6字节
  *         
  *         典型数据包结构：
  *         [0xFF] [DATA0] [DATA1] [DATA2] [DATA3] [0xFE]
  */
void Serial_SendPacket(void)
{
    Serial_SendByte(0xFF);         // 发送起始标志字节(0xFF)
    Serial_SendArray(Serial_TxPack, 4); // 发送数据内容(4字节)
    Serial_SendByte(0xFE);         // 发送结束标志字节(0xFE)
}


/**
  * @brief USART1中断服务函数
  * 
  * 此函数处理USART1的所有中断事件，主要实现一个简单的串口通信协议的状态机：
  *   - 协议格式: 0xFF + 4字节数据 + 0xFE
  *   - 使用状态机(RxState)解析数据包
  *   - 完整接收后设置Serial_RxFlag标志位
  * 
  * 工作流程：
  *   1. 等待起始字节0xFF（状态0）
  *   2. 接收4字节数据（状态1）
  *   3. 验证结束字节0xFE（状态2）
  *   4. 设置接收完成标志
  * 
  * 注意：使用静态变量保存状态，支持多次调用保持状态
  */
void USART1_IRQHandler(void)
{
    static uint8_t RxState = 0;   // 接收状态机状态 (0:等待起始符 1:接收数据 2:等待结束符)
    static uint8_t pRxState = 0;  // 数据包接收位置指针 (0-3)

    /* 检查USART1接收中断标志位（RXNE） */
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
    {
        // 从数据寄存器读取接收到的字节
        uint8_t RxData = USART_ReceiveData(USART1);
        
        /* 状态机处理 */
        if (RxState == 0)  // 状态0：等待数据包起始标志
        {
            if (RxData == 0xFF)  // 检测到起始字节
            {
                RxState = 1;     // 进入数据接收状态
                pRxState = 0;    // 重置数据包指针
            }
        }
        else if (RxState == 1)  // 状态1：接收数据包内容
        {
            Serial_RxPack[pRxState] = RxData;  // 存储数据到接收缓冲区
            pRxState++;                        // 指针位置递增
            
            if (pRxState >= 4)  // 已接收4字节数据
            {
                RxState = 2;  // 进入结束符验证状态
            }
        }
        else if (RxState == 2)  // 状态2：验证数据包结束标志
        {
            if (RxData == 0xFE)  // 检测到结束字节
            {
                RxState = 0;           // 重置状态机
                Serial_RxFlag = 1;     // 设置接收完成标志
            }
        }
        
        // 清除接收中断标志位（重要！避免重复进入中断）
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);  
    }
}