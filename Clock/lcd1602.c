#include "LCD1602.H"
#include "stc15.h"
#include <stdarg.h>
#include <stdio.h>  // 使用 vsprintf 进行字符串格式化

// 定义LCD的控制引脚
sbit RS = P4^1;    // 选择寄存器 (RS)，控制命令或数据模式
sbit RW = P4^2;    // 读写控制 (RW)，控制读写模式
sbit E = P4^4;     // 使能引脚 (E)
#define P_Data P2  // LCD数据端口


// LCD指令命令
#define LCD_CMD_CLEAR  0x01  // 清屏命令
#define LCD_CMD_HOME   0x02  // 返回原点命令
#define LCD_CMD_ENTRY  0x06  // 输入模式设置命令
#define LCD_CMD_REVERSE_ON  0x08  // 启用反显
#define LCD_CMD_REVERSE_OFF 0x00  // 关闭反显
// 函数原型声明
unsigned char ReadStatus(void);

// 延时函数，单位：毫秒
void DelayNms(u16 i)
{
    u16 j;
    while(i--)
        for(j=0;j<1000;j++);  // 延时循环
}

// 延时函数，单位：时钟周期
void Delay(u16 i)
{
    while(i--);  // 延时循环
}

// LCD指令操作函数
// com: 需要发送的指令字节，例如清屏命令0x01
// chkflag: 若为1，则等待LCD完成当前指令后再返回，否则不等待
void LcdCom(u8 com, bit chkflag)
{
    if(chkflag) ReadStatus();  // 检查LCD状态，确保指令已执行
    
    RS = 0;     // 选择指令寄存器
    RW = 0;     // 设置为写模式
    E = 1;      // 使能信号
    P_Data = com;  // 将指令写入数据总线
    Delay(2);  // 延时，确保指令能够正确执行
    E = 0;     // 关闭使能信号
}

// LCD数据写入函数
// dat: 需要显示的数据字节，可以是字符数据
void LcdData(u8 dat)
{
    ReadStatus();  // 确保LCD已准备好接收数据
    
    RS = 1;     // 选择数据寄存器
    RW = 0;     // 设置为写模式
    E = 1;      // 使能信号
    P_Data = dat;  // 将数据写入数据总线
    Delay(2);  // 延时，确保数据能够正确显示
    E = 0;     // 关闭使能信号
}

// LCD初始化函数
void LcdInit()
{
    DelayNms(10);          // 等待LCD稳定
    LcdCom(0x38, 0);       // 选择8位数据传输模式
    DelayNms(5);
    LcdCom(0x38, 0);       // 再次设置
    DelayNms(5);
    LcdCom(0x38, 0);       // 再次设置
    
    LcdCom(0x38, 1);       // 设置显示模式
    LcdCom(0x01, 1);       // 清除显示
    LcdCom(0x06, 1);       // 设置光标自动右移
    LcdCom(0x0c, 1);       // 开启显示，不显示光标
}

// LCD读取状态
unsigned char ReadStatus(void)
{
    u16 timeout = 5000;   // 超时计数器
    P_Data = 0xFF;        // 设置数据为全1
    RS = 0;               // 选择指令寄存器
    RW = 1;               // 设置为读模式
    E = 0;                // 关闭使能信号
    Delay(2);             // 延时
    E = 1;                // 使能信号
    while ((P_Data & 0x80) && timeout--);  // 检查LCD是否完成操作
    return P_Data;       // 返回LCD的状态值
}

// LCD字符串显示函数
// x: LCD显示的列号，范围从0到15
// y: LCD显示的行号，0为第一行，1为第二行
// str: 需要显示的字符串
void LcdString(u8 x, u8 y, u8 *str)
{
    x += 0x80;  // 根据列号调整起始位置
    if (y == 1) x += 0x40;  // 第二行起始位置偏移
    LcdCom(x, 1);  // 设置LCD的显示位置
    
    while (*str)
    {
        LcdData(*str);  // 显示当前字符
        str++;          // 移动到下一个字符
    }
}

// LCD显示格式化文本的函数
// x: LCD显示的列号，范围从0到15
// y: LCD显示的行号，0为第一行，1为第二行
// format: 格式化字符串，类似printf的格式
// ...: 可变参数，填充format字符串中的占位符
void LcdDisplay(u8 y, u8 x, const char* format, ...)
{
    va_list args;  // 可变参数列表
    char buf[16];  // 用于存储格式化后的字符串

    va_start(args, format);  // 获取可变参数
    vsprintf(buf, format, args);  // 将格式化字符串写入buf
    va_end(args);  // 结束可变参数处理

    LcdString(x, y, (u8 *)buf);  // 显示格式化后的字符串
}


