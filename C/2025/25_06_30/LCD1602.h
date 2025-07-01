#ifndef __LCD1602.H__
#define __LCD1602.H__

void LCD_Delay();
void LCD_WireCommand(unsigned char Command);
void LCD_WireData(unsigned char Data);
void LCD_Init(void);
void LCD_ShowChar(unsigned char Line, unsigned char Column, unsigned char Char);
void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned int Length);
void LCD_ShowSingedNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned int Length);
void LCD_ShowHexNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length);
void LCD_ShowBinNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length);

#endif
