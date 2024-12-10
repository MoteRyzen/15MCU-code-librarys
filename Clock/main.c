#include <stc15.h>
#include "IO_Init.h"
#include "LCD1602.H"
#include "Init_config.h"
//#include "Delay.h"
//#include "Button.h"
//#include "SMG.h"
//#include "EEPROM.h"
//#include "HC06_BT.h"
//#include "Built_In_ADC.h"
#include "key.h"
#include "Clock.h"

void main(void)
 {  
    uint i=0;
    GPIO_Init();
//	LcdInit();
//    Key_Init();
    Clock_Init(); 
    while (1)
    {
        Key_Scan();
        MainSystem();

        
    }
}


























/*

int main(void) {
    //uint fre=0;
	unsigned char i ;
    GPIO_Init();
	LcdInit();
    //Timer0_Init();
   // Timer1_Init();
   // Exter_INT0_Init();
	
    while (1)
    {
		LcdString(0,0,"Hello world");
		
    }
	
}*//*
RE_INT_FRE(&fre);

        Display_DATA(fre/1000%10,fre/100%10,fre/10%10,fre%10);
       //Display_DATA(0,0,0,0);*/
/*
    uint Hours=0,minutes=0,seconds=0,Place=2,Temp[6]=0;
     
    char mode=0,flag1=0,flag2=0,flag3=0,flag4=0;
    Init();
    interrupt_Init();

    while (1) {
        
              //时间设置模式
        if(mode==0){
            Display_DATA(minutes/10%10,minutes%10,seconds/10%10,seconds%10);
            TR0=0;
            ET0=0;
            if (Key_1 == 0) {flag1 = 1;}
            if (flag1 == 1 && Key_1 == 1){minutes++;flag1=0;}

            if (Key_2 == 0) {flag2 = 1;}
            if (flag2 == 1 && Key_2 == 1){minutes--;flag2=0;}

            if (Key_3 == 0) {flag3 = 1;}
            if (flag3 == 1 && Key_3 == 1){seconds++;flag3=0;}

            if (Key_4 == 0) {flag4 = 1;}
            if (flag4 == 1 && Key_4 == 1){seconds--;flag4=0;}
            
            Temp[0]=Hours/10%10;
            Temp[1]=Hours%10;

            Temp[2]=minutes/10%10;
            Temp[3]=minutes%10;

            Temp[4]=seconds/10%10;
            Temp[5]=seconds%10;  
            if(seconds==60){seconds=0;minutes+=1;}
            if(minutes==60)minutes=0;
            if(Hours==24)Hours=0;

            if(seconds==65535){seconds=59;minutes-=1;}
            if(minutes==65535){minutes=59;Hours-=1;}
            if(Hours==65535)Hours=23;
            if(Key_1==0 && Key_2==0)
                mode=1;
        }

        //计时模式
        if(mode==1){
            TR0=1;
            ET0=1;
            
            if (Key_1 == 0) {flag1 = 1;}
            if (flag1 == 1 && Key_1 == 1){Place=0;flag1=0;}

            if (Key_4 == 0) {flag4 = 1;}
            if (flag4 == 1 && Key_4 == 1){Place=2;flag4=0;}

           
            Temp[0]=Hours/10%10;
            Temp[1]=Hours%10;

            Temp[2]=minutes/10%10;
            Temp[3]=minutes%10;

            Temp[4]=seconds/10%10;
            Temp[5]=seconds%10;                        
            


                Display_DATA(Temp[Place],Temp[Place+1],Temp[Place+2],Temp[Place+3]);
            

            getvalue(&seconds);

            if(seconds==60){seconds=0;minutes+=1;}
            if(minutes==60){minutes=0;Hours+=1;}
            if(Hours==24)Hours=0;
            if(Key_1==0 && Key_2==0)
                mode=0;
        }



*/
/*//选择输出PWM（定时器0）
if (Key_1 == 0) {flag[1] = 1;}
            if (flag[1] == 1 && Key_1 == 1){if(parameters<=(100-Delta))parameters+=Delta;flag[1]=0;}
    
            if (Key_2 == 0) {flag[2] = 1;}
            if (flag[2] == 1 && Key_2 == 1){parameters=100;flag[2]=0;} 

            if (Key_3 == 0) {flag[3] = 1;}
            if (flag[3] == 1 && Key_3 == 1){parameters=60;flag[3]=0;}

            if (Key_4 == 0) {flag[4] = 1;}
            if (flag[4] == 1 && Key_4 == 1){parameters=20;flag[4]=0;}
           // Display_DATA(0,0,parameters/10%10,parameters%10);
        Set_Parameters(100,parameters);
        Delta=5;
    */
