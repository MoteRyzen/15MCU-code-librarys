#ifndef __BUILT_IN_ADC_
#define __BUILT_IN_ADC_

/*使用示例
main(){
  InitADC(0x01);                      //初始化ADC
    IE = 0xa0;                      //使能ADC中断
                                    //开始AD转换  
    while (1)
    {
        if(P32==0)
        vol=ADC_to_Voltage(GetADCResult(0));
        //RE_INT_FRE(&fre);
        LcdDisplay(4,0,"%.3f V",vol);
        LcdDisplay(0,1,"ch:%d",ch); 
      //  LcdDisplay(8,0,"L:%d",ADC_Low2_Value);
    }
}
*/
typedef unsigned char BYTE;
typedef unsigned int WORD;
#define uchar unsigned char 
#define uint unsigned int

//串口部分
void InitUart();
void SendData(BYTE dat);

//ADC部分
void InitADC(unsigned char ADC_IO_Address);
BYTE GetADCResult(BYTE ch);
float ADC_to_Voltage(uint adc_value);


extern WORD ADC_Value;
extern WORD ch;
extern WORD ADC_Low2_Value;
#endif