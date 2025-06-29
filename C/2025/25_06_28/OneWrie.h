#ifndef __ONEWIRE.H__
#define __ONEWIRE.H__

unsigned char OneWire_Init(void);
unsigned char OneWire_SendBit(unsigned char Bit);
unsigned char OneWire_ReceiveBit(void);
void OneWire_SendByte(unsigned char Byte);
unsigned char OneWire_ReceiveByte(void);

#endif