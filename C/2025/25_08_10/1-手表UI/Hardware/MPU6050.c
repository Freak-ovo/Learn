#include "stm32f10x.h"  // STM32F10x系列微控制器标准外设库
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS         0xD0

/**
  * @brief  等待指定的I2C事件发生（带超时保护）
  * @param  I2Cx: 使用的I2C外设（如I2C2）
  * @param  I2C_EVENT: 要等待的I2C事件标志
  * @retval 无
  *
  * 功能描述：
  * 该函数用于安全等待指定的I2C事件发生，避免因硬件故障导致程序死锁。
  * 实现机制：
  * 1. 设置超时计数器（当前为10000次循环）
  * 2. 循环检测指定I2C事件是否发生
  * 3. 每次循环递减超时计数器
  * 4. 当计数器归零时强制退出等待
  *
  * 注意事项：
  * - 超时退出表示I2C通信异常，应进行错误处理
  * - 超时阈值需根据系统时钟频率调整
  * - 实际产品中建议返回状态值供上层处理
  */
void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
    /* 设置超时计数器（根据系统时钟调整） */
    uint32_t TimeOut = 10000;
    
    /* 循环检测事件标志 */
    while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)
    {
        TimeOut--;  // 递减超时计数器
        
        /* 超时处理：跳出等待循环 */
        if (TimeOut == 0)
        {
            // 此处可添加错误处理代码
            // 例如：置位错误标志/记录日志/恢复I2C总线等
            break;
        }
    }
    
}
/**
  * @brief 向MPU6050传感器的指定寄存器写入单字节数据
  * @param RegAddress: 目标寄存器地址（8位）
  * @param Data: 要写入的数据（8位）
  * @retval 无
  *
  * 功能描述：
  * 该函数通过I2C2接口向MPU6050传感器执行单寄存器写入操作。
  * 通信过程严格遵循I2C协议，包含以下步骤：
  * 1. 生成起始信号（START）
  * 2. 发送MPU6050器件地址（写模式）
  * 3. 发送目标寄存器地址
  * 4. 发送待写入数据
  * 5. 生成停止信号（STOP）
  * 每个关键步骤后都有硬件事件检测，确保通信可靠性。
  * 
  * 注意：
  * - 使用I2C2接口（需提前初始化）
  * - MPU6050_ADDRESS 应定义为器件7位地址（通常0x68或0x69）
  * - 所有操作均为阻塞式，需等待事件完成才继续执行
  * 时序:START → SLAVE_ADDR(W) → REG_ADDR → DATA → STOP
  */
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
    /* 步骤1：生成I2C起始信号 */
    I2C_GenerateSTART(I2C2, ENABLE);
    /* 等待主模式选择事件：起始信号成功发送 */
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    /* 步骤2：发送器件地址（写模式） */
    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
    /* 等待主发送器模式就绪事件：地址发送成功且收到ACK */
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    /* 步骤3：发送目标寄存器地址 */
    I2C_SendData(I2C2, RegAddress);
    /* 等待字节传输事件：寄存器地址已移入移位寄存器 */
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);

    /* 步骤4：发送待写入数据 */
    I2C_SendData(I2C2, Data);
    /* 等待字节传输完成事件：数据发送完成且收到ACK */
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    /* 步骤5：生成I2C停止信号结束通信 */
    I2C_GenerateSTOP(I2C2, ENABLE);
}

/**
  * @brief  从MPU6050传感器的指定寄存器读取单字节数据
  * @param  RegAddress: 要读取的寄存器地址（8位）
  * @retval 读取到的寄存器数据（8位）
  *
  * 读取流程详解：
  * 1. 启动写操作阶段（设置寄存器指针）：
  *    - 发送起始信号(START)
  *    - 发送MPU6050器件地址 + 写方向位
  *    - 发送目标寄存器地址
  * 2. 重启总线切换为读操作：
  *    - 发送重复起始信号(Repeated Start)
  *    - 发送MPU6050器件地址 + 读方向位
  * 3. 接收数据阶段：
  *    - 配置NACK表示只读取一个字节
  *    - 发送停止信号准备结束通信
  *    - 等待数据接收完成
  *    - 读取接收到的数据
  * 4. 恢复ACK配置（为后续通信做准备）
  * 
  * 注意事项：
  * - 使用I2C2接口（需提前初始化）
  * - MPU6050_ADDRESS 应定义为器件7位地址（通常0x68或0x69）
  * - 采用标准I2C寄存器读取流程：先写寄存器地址，再重启总线读数据
  */
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
    uint8_t Data;

    /* === 阶段1：设置目标寄存器地址 === */
    
    /* 步骤1.1：生成I2C起始信号 */
    I2C_GenerateSTART(I2C2, ENABLE);
    /* 等待主模式选择事件：起始信号成功发送 */
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    /* 步骤1.2：发送器件地址（写模式） */
    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
    /* 等待主发送器模式就绪事件：地址发送成功且收到ACK */
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    /* 步骤1.3：发送目标寄存器地址 */
    I2C_SendData(I2C2, RegAddress);
    /* 等待字节传输事件：寄存器地址已移入移位寄存器 */
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);


    /* === 阶段2：重启总线切换为读操作 === */
    
    /* 步骤2.1：生成重复起始信号(Repeated Start) */
    I2C_GenerateSTART(I2C2, ENABLE);
    /* 等待主模式选择事件：重复起始信号成功发送 */
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    /* 步骤2.2：发送器件地址（读模式） */
    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Receiver);
    /* 等待主接收器模式就绪事件：地址发送成功且收到ACK */
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);


    /* === 阶段3：接收数据 === */
    
    /* 配置NACK：表示这是最后一个要接收的字节 */
    I2C_AcknowledgeConfig(I2C2, DISABLE);
    
    /* 提前发送停止信号（将在数据接收完成后自动生效） */
    I2C_GenerateSTOP(I2C2, ENABLE);

    /* 等待字节接收完成事件：数据已接收至DR寄存器 */
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED);

    /* 读取接收到的数据 */
    Data = I2C_ReceiveData(I2C2);

    /* 恢复ACK配置（使能应答）为后续通信做准备 */
    I2C_AcknowledgeConfig(I2C2, ENABLE);

    return Data; 
}


/**
  * @brief  初始化MPU6050传感器
  * @param  None
  * @retval None
  * @note   本函数执行以下初始化操作：
  *          1. 初始化I2C总线并配置GPIO
  *          2. 配置MPU6050的电源管理、采样率、滤波器及量程
  *          3. 设置加速度计和陀螺仪的工作参数
  *          4. 使能所有传感器轴
  * 
  *         关键配置说明：
  *          - 采样率: 100Hz (陀螺仪1kHz分频)
  *          - 数字低通滤波器: 5Hz带宽
  *          - 陀螺仪量程: ±2000°/s
  *          - 加速度计量程: ±16g (启用Z轴自检)
  */
void MPU6050_Init(void)
{
    /* 初始化I2C外设时钟和GPIO */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /* 配置I2C引脚为复用开漏模式 */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;     // 复用开漏模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;  // PB10:SCL, PB11:SDA
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   // 高速模式
    GPIO_Init(GPIOB, &GPIO_InitStructure);	

    /* 配置I2C通信参数 */
    I2C_InitTypeDef I2C_InitStructure;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;         // 使能应答
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;  // 7位地址模式
    I2C_InitStructure.I2C_ClockSpeed = 50000;           // 50kHz总线速度
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;  // Tlow/Thigh = 2
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;          // I2C标准模式
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;           // 主机地址(未使用)
    I2C_Init(I2C2, &I2C_InitStructure);

    I2C_Cmd(I2C2, ENABLE);  // 使能I2C2外设

    /* 传感器核心配置 */
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);    // 电源管理1: 时钟源选择X轴陀螺仪
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);    // 电源管理2: 使能所有传感器轴
    
    /* 采样与滤波配置 */
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);    // 采样分频: 100Hz采样率(1kHz/(1+9))
    MPU6050_WriteReg(MPU6050_CONFIG, 0x06);        // 配置寄存器: 设置5Hz数字低通滤波器
    
    /* 传感器量程配置 */
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);   // 陀螺仪配置: ±2000°/s量程
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x19);  // 加速度计配置: ±16g量程 + Z轴自检
}

/**
  * @brief  从MPU6050传感器获取加速度计和陀螺仪的原始数据
  * @param  AccX  指向存储X轴加速度计原始数据的int16_t指针
  * @param  AccY  指向存储Y轴加速度计原始数据的int16_t指针
  * @param  AccZ  指向存储Z轴加速度计原始数据的int16_t指针
  * @param  GyroX 指向存储X轴陀螺仪原始数据的int16_t指针
  * @param  GyroY 指向存储Y轴陀螺仪原始数据的int16_t指针
  * @param  GyroZ 指向存储Z轴陀螺仪原始数据的int16_t指针
  * @retval 无
  *
  * @note 函数通过I2C读取MPU6050的传感器寄存器
  *       每个轴的测量值由两个8位寄存器（高字节和低字节）组成
  *       需要将高低字节组合成16位有符号整数
  */
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
                    int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
    uint8_t DataL, DataH;  // 用于存储寄存器读取的低字节(L)和高字节(H)
    
    // 读取X轴加速度计数据
    DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);  // 读取加速度计X轴高字节
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);  // 读取加速度计X轴低字节
    *AccX = (DataH << 8) | DataL;  // 合并高低字节 -> [15:8] | [7:0]

    // 读取Y轴加速度计数据
    DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
    *AccY = (DataH << 8) | DataL;

    // 读取Z轴加速度计数据
    DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
    *AccZ = (DataH << 8) | DataL;

    // 读取X轴陀螺仪数据
    DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);  // 读取陀螺仪X轴高字节
    DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);  // 读取陀螺仪X轴低字节
    *GyroX = (DataH << 8) | DataL;

    // 读取Y轴陀螺仪数据
    DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
    *GyroY = (DataH << 8) | DataL;

    // 读取Z轴陀螺仪数据
    DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
    *GyroZ = (DataH << 8) | DataL;
}

/**
  * @brief  获取MPU6050设备的ID
  * @note   该函数通过读取MPU6050的WHO_AM_I寄存器（设备身份寄存器）获取芯片ID。
  *         根据MPU6050手册，该寄存器默认值为0x68（二进制01101000），
  *         其中高6位是固定值（011010），低2位由硬件地址引脚决定。
  * @retval uint8_t 返回的7位设备ID值（实际有效位为高6位+低2位地址）
  */
uint8_t MPU6050_GetID(void)
{
  // 调用底层寄存器读取函数
  // 参数 MPU6050_WHO_AM_I：MPU6050设备身份寄存器的预定义地址（通常为0x75）
  return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

