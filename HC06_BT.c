#include "HC06_BT.h"
#include"stc15.h"

#define FOSC 11059200L          //系统频率
#define BAUD 9600             //串口波特率

unsigned char received;

//串口1初始化 
//默认定时器4
void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
    AUXR = 0x40;                //定时器1为1T模式
    TMOD = 0x00;                //定时器1为模式0(16位自动重载)
    TL1 = (65536 - (FOSC/4/BAUD));   //设置波特率重装值
    TH1 = (65536 - (FOSC/4/BAUD))>>8;
    TR1 = 1;                    //定时器1开始启动
    ES = 1;                     //使能串口中断
    EA = 1;
}
 

//发送数据
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;    //把Byte的值赋给缓存SBUF
	while(TI==0); //确认发送控制器TI标志位的状态，只有当TI不等于0时，才会跳出循环
	TI=0;         //清除发送完成标志位
}

//接收数据中断
void UART_Routine() interrupt 4
{
	if(RI==1)                   //判断接收中断请求标志位是否置1
	{
		RI=0;                   //清空标志位，复位
        received=SBUF;          //接受的数据
        //------------          //或者添加回调函数
		UART_SendByte(SBUF);    //执行发送数据函数，将数据发回电脑
	}
}


