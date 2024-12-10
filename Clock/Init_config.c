//
// Created by mote on 2024/11/4.
//

#include "Init_config.h"
#include "stc15.h"
#include "key.h"
//#include "Beep.h"
//#include "Button.h"
//#include "SMG.h"
/*
uint frequency=0;
uint Re_int_Fre=0;

void RE_INT_FRE(uint *p){
        *p=Re_int_Fre;  
}
void Count_fre(){
    Re_int_Fre= frequency;
}

//-----------------定时器1------------------------------ //

void Timer1_Init(){
 	
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL1=T1MS;	//设置定时初值
	TH1=T1MS>>8;		//设置定时初值
	TF1 = 0;		//清除TF0标志
	TR1 = 1;		//定时器0开始计时
    ET1 = 1;                        //使能定时器0中断
    EA = 1;
}
void Timer1_ISR() interrupt 8 using 1  
{
    static uchar i=0;
    
    if(++i>=10){
      //  Key_Scan();
        i=0;
    }
                       
}
*/
char *p;
void getvalue(char *i){
    p=i;//指针指向局部变量seconds的地址
}
//-----------------定时器0------------------------------ //
// Timer0 interrupt routine //
//1ms中断/* main program *///10us
void Timer0_Init(){
    AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0=T1MS;	//设置定时初值
	TH0=T1MS>>8;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
//    ET0 = 1;                        //使能定时器0中断
    EA = 1;
}

void Timer0_ISR(void)interrupt 1 using 1 
{
    static uint i=0;
    i++;  
   if(i>=1000)
        {
           *p+=1;//指针指向seconds，seconds每秒+1
           i=0;
        }
    
}
/*
//-----------------外部中断0------------------------------ //
//
void EXINT_0() interrupt 0       //INT0中断入口
{      
        frequency+=1; 
       
}

void Exter_INT0_Init(){
    INT0 = 1;
    IT0 = 1;                    //设置INT0的中断类型 (1:仅下降沿 0:上升沿和下降沿)
    EX0 = 1;                    //使能INT0中断
    EA = 1;
}


//-----------------------------------------------



//输出PWM
void Timer0_ISR(void)interrupt 1
{
    static unsigned int Counter=0;
    TL0=T1MS;
    TH0=T1MS>>8;
    Counter++;
    if (Counter>=Period)
        Counter=0;
    if(Counter>=Compare){
        P00=1;     
    }
    else{
        P00=0;
    }    
}
uint Compare=50;
uint Period=100;
void Set_Parameters(uint period,uint Set_High_Reverse_State){
   // Set_Count_state=SetCountState;
    Compare=Set_High_Reverse_State;
    Period=period;
}
*/





        

