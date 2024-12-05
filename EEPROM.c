//
// Created by mote on 2024/9/26.
//

#include "EEPROM.h"
#include "stc15.h"
#include "intrins.h"

// 写入EEPROM函数
void IAP_WriteByte(WORD addr, WORD dat) {
    IAP_ADDRH = (addr >> 8) & 0xFF;  // 高字节地址
    IAP_ADDRL = addr & 0xFF;         // 低字节地址
    IAP_DATA = dat;                  // 要写入的数据
    IAP_CMD = IAP_CMD_WRITE;         // 设置为写操作
    IAP_TRIG = 0x5A;                 // 启动写操作
    IAP_TRIG = 0xA5;                 // 双重触发命令
    _nop_();                         // 等待操作完成
    IAP_CMD = IAP_CMD_IDLE;          // 结束IAP操作
}

// 读取EEPROM函数
WORD IAP_ReadByte(WORD addr) {
    IAP_ADDRH = (addr >> 8) & 0xFF;  // 高字节地址
    IAP_ADDRL = addr & 0xFF;         // 低字节地址
    IAP_CMD = IAP_CMD_READ;          // 设置为读操作
    IAP_TRIG = 0x5A;                 // 启动读操作
    IAP_TRIG = 0xA5;                 // 双重触发命令
    _nop_();                         // 等待操作完成
    IAP_CMD = IAP_CMD_IDLE;          // 结束IAP操作
    return IAP_DATA;                 // 返回读取的数据
}

// 写入变量到EEPROM
void write_variable_to_eeprom(WORD addr, WORD Data) {
    IAP_WriteByte(addr, (Data >> 8) & 0xFF);   // 写入高字节
    IAP_WriteByte(addr + 1, Data & 0xFF);      // 写入低字节
}

// 从EEPROM读取变量
WORD read_variable_from_eeprom(WORD addr) {
    WORD _data = 0;
    _data = IAP_ReadByte(addr) << 8;            // 读取高字节
    _data |= IAP_ReadByte(addr + 1);            // 读取低字节
    return _data;
}

