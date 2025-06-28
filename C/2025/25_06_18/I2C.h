#ifndef __IIC.H__
#define __IIC.H__

void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(unsigned char Byte);
void I2C_ReceiveByte(void);
void I2C_SendAck(unsigned char AckBit);
unsigned char I2C_ReceiveAck(void);



#endif
