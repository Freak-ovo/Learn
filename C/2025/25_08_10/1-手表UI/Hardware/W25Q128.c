#include "stm32f10x.h"  // STM32F10x系列微控制器标准外设库
#include "MySPI.h"
#include "W25Q128_Ins.h"


/**
  * @brief  W25Q128 初始化函数
  * @note   初始化底层SPI通信接口
  *         该函数只需在系统启动时调用一次
  */
void W25Q128_Init(void)
{
    MySPI_Init();  // 初始化SPI的GPIO引脚和默认状态
}

/**
  * @brief  发送写使能指令到W25Q128芯片
  * @param  无
  * @retval 无
  * @note   该指令用于设置芯片内部的写使能锁存器（WEL）
  *         在执行任何修改存储器的操作前必须调用此函数
  * 
  * 时序流程：
  *   1. 启动SPI通信（拉低CS）
  *   2. 发送写使能指令码（0x06）
  *   3. 停止SPI通信（释放CS）
  * 
  * 重要特性：
  *   - 使能后状态寄存器的WEL位（bit1）会被置1
  *   - 写使能状态在以下情况自动清除：
  *       1. 完成页编程/擦除操作
  *       2. 收到写失能指令（0x04）
  *       3. 设备断电
  *       4. 发生写保护错误
  */
void W25Q128_WriteEnable(void)
{
    // 启动SPI通信（拉低CS片选信号）
    MySPI_Start();
    
    // 发送写使能指令（0x06）
    // 该指令不需要地址或数据参数
    MySPI_SwapByte(W25Q128_WRITE_ENABLE);
    
    // 停止SPI通信（释放CS片选信号）
    MySPI_Stop();
}

/**
  * @brief  读取W25Q128闪存芯片的制造商ID和设备ID
  * @param  MID: 指向存储制造商ID的变量的指针
  *            - 类型：uint8_t*（8位无符号整数指针）
  *            - 函数执行后，此指针指向的位置将包含读取到的制造商ID
  * @param  DID: 指向存储设备ID的变量的指针
  *            - 类型：uint16_t*（16位无符号整数指针）
  *            - 函数执行后，此指针指向的位置将包含完整的设备ID（高字节+低字节）
  * 
  * @note   此函数通过SPI接口发送JEDEC ID命令(0x9F)并读取3字节响应数据
  *         响应数据格式：
  *          - 第1字节: 制造商ID（如Micron为0x20，Winbond为0xEF）
  *          - 第2字节: 设备ID高字节（包含存储器类型信息）
  *          - 第3字节: 设备ID低字节（包含容量信息）
  *
  *         完整的设备ID = (第2字节 << 8) | 第3字节
  *         例如：NM25Q128的完整设备ID为0xBA18
  *
  *         通信时序:
  *         1. 拉低片选(SS)启动通信（选中芯片）
  *         2. 发送JEDEC ID命令字节0x9F
  *         3. 读取制造商ID(MID) - 第1个响应字节
  *         4. 读取设备ID高字节 - 第2个响应字节
  *         5. 读取设备ID低字节 - 第3个响应字节
  *         6. 拉高片选(SS)结束通信（释放芯片）
  * 
  *         注意：读取数据时主机需要发送虚拟字节(0xFF)以产生时钟信号
  */
void W25Q128_ReadID(uint8_t *MID, uint16_t *DID)
{
    // 启动SPI传输：拉低片选信号(SS)，选中W25Q128芯片
    MySPI_Start();
    
    // 发送JEDEC ID命令(0x9F)到W25Q128
    // W25Q128_JEDEC_ID是预定义的宏，值为0x9F
    MySPI_SwapByte(W25Q128_JEDEC_ID);
    
    // 读取制造商ID（第1个响应字节）
    // 发送虚拟字节0xFF(W25Q128_DUMMY_BYTE)产生时钟信号
    // 读取到的值存入MID指针指向的位置
    *MID = MySPI_SwapByte(W25Q128_DUMMY_BYTE);
    
    // 读取设备ID高字节（第2个响应字节）
    // 1. 首先读取设备ID高字节到DID指针指向的变量
    //    （此时*DID的低8位包含设备ID高字节）
    *DID = MySPI_SwapByte(W25Q128_DUMMY_BYTE);
    
    // 2. 将设备ID高字节左移8位
    //    此时*DID的高8位包含设备ID高字节，低8位为0
    *DID <<= 8;
    
    // 读取设备ID低字节（第3个响应字节）
    // 1. 读取设备ID低字节
    // 2. 与之前左移后的值进行位或操作
    //    结果：*DID = (设备ID高字节 << 8) | 设备ID低字节
    *DID |= MySPI_SwapByte(W25Q128_DUMMY_BYTE);
    
    // 结束SPI传输：拉高片选信号(SS)，释放W25Q128芯片
    MySPI_Stop();
}

/**
  * @brief  等待W25Q64芯片完成内部操作（擦除/写入）
  * @param  无
  * @retval 无
  * @note   通过轮询状态寄存器忙标志位，直到操作完成或超时
  */
void W25Q128_WaitBusy(void)
{
    uint32_t TimeOut = 100000;  // 超时计数器（防止无限等待）
    
    // 启动SPI通信
    MySPI_Start();
    
    // 发送读取状态寄存器1的命令（指令码0x05）
    MySPI_SwapByte(W25Q128_READ_STATUS_REGISTER_1);
    
    // 循环检测BUSY位（状态寄存器bit0）
    // 当状态寄存器bit0=1时表示芯片繁忙，需要持续等待
    while ((MySPI_SwapByte(W25Q128_DUMMY_BYTE) & 0x01) == 0x01)
    {
        TimeOut--;  // 每次循环递减超时计数器
        if (TimeOut == 0)
        {
            break;  // 超时强制退出（防止死锁）
        }
    }
    
    // 停止SPI通信
    MySPI_Stop();
}

/**
  * @brief  向W25Q128 Flash芯片执行页编程操作（写入数据）
  * @param  Address    : 目标起始地址（24位地址）
  * @param  DataArray  : 要写入的数据数组指针
  * @param  Count      : 要写入的字节数（最大256字节）
  * @retval 无
  * @note   页编程操作必须在擦除后的区域进行（只能将1改为0）
  *         跨页写入会自动回卷到页首，需调用者确保不跨页
  */
void W25Q128_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count)
{
    // 1. 使能芯片写操作（设置内部写使能锁存器）
    W25Q128_WriteEnable();
    
    // 2. 启动SPI通信（拉低CS片选信号）
    MySPI_Start();
    
    // 3. 发送页编程指令（0x02）
    MySPI_SwapByte(W25Q128_PAGE_PROGRAM);
    
    // 4. 发送24位目标地址（高位在前）
    MySPI_SwapByte(Address >> 16);  // 地址23-16位
    MySPI_SwapByte(Address >> 8);   // 地址15-8位
    MySPI_SwapByte(Address);        // 地址7-0位
    
    // 5. 连续写入数据
    for (uint16_t i = 0; i < Count; i++)
    {
        MySPI_SwapByte(DataArray[i]);  // 逐字节发送数据
    }
    
    // 6. 结束SPI通信（释放CS片选信号）
    MySPI_Stop();
    
    // 7. 等待芯片完成内部编程操作
    W25Q128_WaitBusy();
}

/**
  * @brief  擦除W25Q128芯片的4KB扇区
  * @param  Address : 目标扇区内的任意地址（24位地址）
  * @retval 无
  * @note   擦除操作将整个4KB扇区置为0xFF（全1状态）
  *         擦除时间约100-400ms，需等待操作完成
  */
void W25Q128_SectorErase(uint32_t Address)
{
    // 1. 使能芯片写操作（设置内部写使能锁存器）
    W25Q128_WriteEnable();
    
    // 2. 启动SPI通信（拉低CS片选信号）
    MySPI_Start();
    
    // 3. 发送扇区擦除指令（0x20）
    MySPI_SwapByte(W25Q128_SECTOR_ERASE_4KB);
    
    // 4. 发送24位地址（高位在前）
    // 注意：实际使用地址的[23:12]位确定扇区，低位地址被忽略
    MySPI_SwapByte(Address >> 16);  // 地址23-16位
    MySPI_SwapByte(Address >> 8);   // 地址15-8位
    MySPI_SwapByte(Address);        // 地址7-0位（仅高4位有效）
    
    // 5. 结束SPI通信（释放CS片选信号）
    MySPI_Stop();
    
    // 6. 等待芯片完成擦除操作（阻塞等待）
    W25Q128_WaitBusy();
}

/**
  * @brief  从W25Q128 Flash芯片读取数据
  * @param  Address   : 读取起始地址（24位地址）
  * @param  DataArray : 存储读取数据的数组指针
  * @param  Count     : 要读取的字节数（无长度限制）
  * @retval 无
  * @note   支持跨页连续读取，最高时钟频率133MHz
  *         读取操作不会改变存储内容（非破坏性）
  */
void W25Q128_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
    // 1. 启动SPI通信（拉低CS片选信号）
    MySPI_Start();
    
    // 2. 发送读数据指令（0x03）
    MySPI_SwapByte(W25Q128_READ_DATA);
    
    // 3. 发送24位起始地址（高位在前）
    MySPI_SwapByte(Address >> 16);  // 地址23-16位
    MySPI_SwapByte(Address >> 8);   // 地址15-8位
    MySPI_SwapByte(Address);        // 地址7-0位
    
    // 4. 连续读取数据
    // 注意：通过发送哑字节（0xFF）来获取芯片返回的数据
    for (uint32_t i = 0; i < Count; i++)
    {
        // 每次SPI交换操作：发送0xFF，同时接收1字节数据
        DataArray[i] = MySPI_SwapByte(W25Q128_DUMMY_BYTE);
    }
    
    // 5. 结束SPI通信（释放CS片选信号）
    MySPI_Stop();
}
