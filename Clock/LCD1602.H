#ifndef __LCD1602_H
#define __LCD1602_H

#define u8 unsigned char
#define u16 unsigned int

void LcdInit();
void LcdString(u8 x, u8 y, u8 *str);
//void LcdBuffer(u8 x, u8 y, u8 *str, u8 n);
void LcdDisplay(u8 y, u8 x, const char* format, ...);
void LcdDisplay_Reverse(u8 y, u8 x, const char* format, u8 reverse, ...);

#endif