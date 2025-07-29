#include "stm32f10x.h"  // STM32F10x系列微控制器标准外设库
#include "MyIIC.h"
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS         0xD0

/**
  * @brief 向MPU6050的指定寄存器写入数据
  * @param RegAddress: 目标寄存器地址（8位）
  * @param Data: 要写入的数据（8位）
  * @retval 无
  *
  * 函数通过I2C协议执行以下操作：
  * 1. 启动I2C通信
  * 2. 发送MPU6050的器件地址（写模式）
  * 3. 发送目标寄存器地址
  * 4. 发送要写入的数据
  * 5. 停止I2C通信
  * 每个步骤后都进行应答检测确保通信正常
  */
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
    MyIIC_Start();                  // 发起I2C起始信号
    
    MyIIC_SendByte(MPU6050_ADDRESS);// 发送MPU6050器件地址 + 写位(通常地址左移1位后末位为0)
    MyIIC_ReceiveAck();             // 检测从机应答（确保设备在线）
    
    MyIIC_SendByte(RegAddress);     // 发送要操作的寄存器地址
    MyIIC_ReceiveAck();             // 检测从机应答（确保地址有效）
    
    MyIIC_SendByte(Data);           // 向寄存器写入数据
    MyIIC_ReceiveAck();             // 检测从机应答（确保数据接收成功）
    
    MyIIC_Stop();                   // 发起I2C停止信号
}

/**
  * @brief  从MPU6050的指定寄存器读取数据
  * @param  RegAddress: 要读取的寄存器地址（8位）
  * @retval 读取到的寄存器数据（8位）
  *
  * 读取流程：
  * 1. 启动写操作：发送器件地址+写位
  * 2. 发送目标寄存器地址
  * 3. 重启I2C总线（Repeated Start）
  * 4. 启动读操作：发送器件地址+读位
  * 5. 接收数据字节（主机发送NACK表示读取结束）
  * 6. 发送停止信号
  */
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
    uint8_t Data;
    
    // --- 写阶段：设置寄存器指针 ---
    MyIIC_Start();                      // 发起I2C起始信号
    MyIIC_SendByte(MPU6050_ADDRESS);    // 发送器件地址 + 写位(0)
    MyIIC_ReceiveAck();                 // 检测从机应答
    MyIIC_SendByte(RegAddress);         // 发送要读取的寄存器地址
    MyIIC_ReceiveAck();                 // 检测从机应答
    
    // --- 读阶段：获取寄存器数据 ---
    MyIIC_Start();                      // 发起重复起始信号(Repeated Start)
    MyIIC_SendByte(MPU6050_ADDRESS | 0x01); // 发送器件地址 + 读位(1)
    MyIIC_ReceiveAck();                 // 检测从机应答
    
    Data = MyIIC_ReceiveByte();         // 接收数据字节
    MyIIC_SendAck(1);                   // 发送NACK（非应答）表示读取结束
    
    MyIIC_Stop();                       // 发起I2C停止信号
    
    return Data;                        // 返回读取到的数据
}



/**
  * @brief  MPU6050传感器初始化函数
  * @param  无
  * @retval 无
  * @note   配置MPU6050的基本工作参数，包括电源管理、采样率、滤波器和量程设置
  */
void MPU6050_Init(void)
{
    // 初始化I2C总线
    MyIIC_Init();
    
    // 配置电源管理寄存器1 (0x6B):
    // 写入0x01 = 0000 0001
    //   - Bit6: SLEEP=0 (退出睡眠模式)
    //   - Bit[2:0]: CLKSEL=001 (选择X轴陀螺仪作为时钟源)
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
    
    // 配置电源管理寄存器2 (0x6C):
    // 写入0x00 = 0000 0000
    //   - 使能所有加速度计轴(X/Y/Z)和陀螺仪轴(X/Y/Z)
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
    
    // 配置采样率分频器 (0x19):
    // 写入0x09 = 0000 1001
    //   - 设置采样率 = 陀螺仪输出率 / (1 + 9) = 1000Hz / 10 = 100Hz
    //   - (假设DLPF启用时陀螺仪输出率为1kHz)
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
    
    // 配置滤波器设置 (0x1A):
    // 写入0x06 = 0000 0110
    //   - Bit[2:0] DLPF_CFG=110 (设置数字低通滤波器带宽为5Hz)
    MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
    
    // 配置陀螺仪量程 (0x1B):
    // 写入0x18 = 0001 1000
    //   - Bit[4:3] FS_SEL=11 (设置满量程范围为±2000°/秒)
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
    
    // 配置加速度计量程 (0x1C):
    // 写入0x19 = 0001 1001
    //   - Bit[4:3] AFS_SEL=11 (设置满量程范围为±16g)
    //   - Bit5: ZA_ST=1 (使能Z轴加速度计自检 - 可选配置)
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x19);
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

