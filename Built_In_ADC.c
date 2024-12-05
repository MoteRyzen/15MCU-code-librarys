#include "Built_In_ADC.h"
#include "intrins.h"
#include "stc15.h"

#define FOSC    11059200L
#define BAUD    9600

#define     URMD    0           //0:使用定时器2作为波特率发生器
                                //1:使用定时器1的模式0(16位自动重载模式)作为波特率发生器
                                //2:使用定时器1的模式2(8位自动重载模式)作为波特率发生器

#define ADC_POWER   0x80            //ADC电源控制位
#define ADC_FLAG    0x10            //ADC完成标志
#define ADC_START   0x08            //ADC起始控制位
#define ADC_SPEEDLL 0x00            //540个时钟
#define ADC_SPEEDL  0x20            //360个时钟
#define ADC_SPEEDH  0x40            //180个时钟
#define ADC_SPEEDHH 0x60            //90个时钟

WORD ch = 0;                        //ADC通道号
WORD ADC_Value = 0;
WORD ADC_Low2_Value = 0;
void ADC_Delay(WORD n);


#define SLOPE 0.0187
#define OFFSET 0.22565

// 函数：将 ADC 数值转换为电压
float ADC_to_Voltage(uint adc_value) {
    // 计算电压
    return SLOPE * adc_value + OFFSET;
}

BYTE GetADCResult(BYTE ch)
{
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
    _nop_();                        //等待4个NOP
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));//等待ADC转换完成
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC
    
    ADC_Low2_Value = ADC_RESL;      //低位数据备份
    ADC_Value=ADC_RES;              //高位数据备份
    
    return ADC_RES;                 //返回ADC结果
}




/*----------------------------
初始化ADC
----------------------------*/
void InitADC(unsigned char ADC_IO_Address)
{
    P1ASF = ADC_IO_Address;                   //设置P1口为AD口
    ADC_RES = 0;                    //清除结果寄存器
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ch;
    ADC_Delay(2);                       //ADC上电并延时

}

/*----------------------------
初始化串口
----------------------------*/
void InitUart()
{
    SCON = 0x5a;                //设置串口为8位可变波特率
#if URMD == 0
    T2L = 0xd8;                 //设置波特率重装值
    T2H = 0xff;                 //115200 bps(65536-18432000/4/115200)
    AUXR = 0x14;                //T2为1T模式, 并启动定时器2
    AUXR |= 0x01;               //选择定时器2为串口1的波特率发生器
#elif URMD == 1
    AUXR = 0x40;                //定时器1为1T模式
    TMOD = 0x00;                //定时器1为模式0(16位自动重载)
    TL1 = 0xd8;                 //设置波特率重装值
    TH1 = 0xff;                 //115200 bps(65536-18432000/4/115200)
    TR1 = 1;                    //定时器1开始启动
#else
    TMOD = 0x20;                //设置定时器1为8位自动重装载模式
    AUXR = 0x40;                //定时器1为1T模式
    TH1 = TL1 = 0xfb;           //115200 bps(256 - 18432000/32/115200)
    TR1 = 1;
#endif
}

/*----------------------------
发送串口数据
----------------------------*/

/*
void adc_isr() interrupt 5 using 1
{   
    static unsigned int i=0;
    if(++i>=10000){

    ADC_CONTR &= !ADC_FLAG;         //清除ADC中断标志

    ADC_Value=ADC_RES;
    ADC_Low2_Value=ADC_LOW2;

    SendData(ch);                   //显示通道号
    SendData(ADC_RES);              //读取高8位结果并发送到串口


    
  //  if (++ch > 7) ch = 0;           //切换到下一个通道
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ch;
    i=0;
    }
}
*/
    //SendData(ch);                   //显示通道号
    //SendData(GetADCResult(ch));     //显示ADC高8位结果
    //SendData(ADC_LOW2);           //显示低2位结果


void SendData(BYTE dat)
{
    while (!TI);                    //等待前一个数据发送完成
    TI = 0;                         //清除发送标志
    SBUF = dat;                     //发送当前数据
}

/*----------------------------
软件延时
----------------------------*/
void ADC_Delay(WORD n)
{
    WORD x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}
