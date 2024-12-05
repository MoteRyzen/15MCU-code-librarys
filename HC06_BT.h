#ifndef HC06_BT_H
#define HC06_BT_H
/*声明:
                    在IAP15w4k61s4开发板环境下，

------------------  默认使用@ P30(RXd)，P31(TXd)------------------------
  ---使用方法
 
  main(){
  ----------------------------------  
    UartInit();  // 初始化串口
    LcdString(0,0,"data:");//初始化lcd  
    while (1)
    {
        LcdDisplay(5,0,"%c",received);//lcd显示
      //UART_SendByte2(a);  //发送'a'字符或者ASCII码“97”  
    }
}
*/

//9600bps@11.0592MHz
void UartInit(void);
void UART_SendByte(unsigned char Byte);

extern unsigned char received;

#endif // HC06_BT_H
