//
// Created by mote on 2024/9/26.
//

#ifndef _EEPROM_H
#define _EEPROM_H




#define IAP_CMD_IDLE  0     // 空闲模式
#define IAP_CMD_READ  1     // 读操作
#define IAP_CMD_WRITE 2     // 写操作
#define IAP_CMD_ERASE 3     // 擦除操作

#define EEPROM_START_ADDR  0x0400  // EEPROM的起始地址
//本示例在Keil开发环境下请选择Intel的8058芯片型号进行编译
//若无特别说明,工作频率一般为11.0592MHz

#define _nop_() __asm NOP __endasm


typedef unsigned char BYTE;
typedef unsigned int WORD;

//-----------------------------------------------


// 写入EEPROM函数
void IAP_WriteByte(WORD addr, WORD dat) ;

// 读取EEPROM函数
WORD IAP_ReadByte(WORD addr) ;

// 写入变量到EEPROM
void write_variable_to_eeprom(WORD addr, WORD Data) ;

// 从EEPROM读取变量
WORD read_variable_from_eeprom(WORD addr) ;





/*

__sfr IAP_DATA    =   0xC2;           //IAP数据寄存器
sfr IAP_ADDRH   =   0xC3;           //IAP地址寄存器高字节
sfr IAP_ADDRL   =   0xC4;           //IAP地址寄存器低字节
sfr IAP_CMD     =   0xC5;           //IAP命令寄存器
sfr IAP_TRIG    =   0xC6;           //IAP命令触发寄存器
sfr IAP_CONTR   =   0xC7;           //IAP控制寄存器*/

#define CMD_IDLE    0               //空闲模式
#define CMD_READ    1               //IAP字节读命令
#define CMD_PROGRAM 2               //IAP字节编程命令
#define CMD_ERASE   3               //IAP扇区擦除命令

//#define ENABLE_IAP 0x80           //if SYSCLK<30MHz
//#define ENABLE_IAP 0x81           //if SYSCLK<24MHz
//#define ENABLE_IAP  0x82            //if SYSCLK<20MHz
#define ENABLE_IAP 0x83           //if SYSCLK<12MHz
//#define ENABLE_IAP 0x84           //if SYSCLK<6MHz
//#define ENABLE_IAP 0x85           //if SYSCLK<3MHz
//#define ENABLE_IAP 0x86           //if SYSCLK<2MHz
//#define ENABLE_IAP 0x87           //if SYSCLK<1MHz

//测试地址
#define IAP_ADDRESS 0x0400





#endif //DEFAULT_EEPROM_H
