//
// Created by mote on 2024/9/25.
//

#include "SMG.h"
#include "stc15.h"
#include "Delay.h"



//uchar a[8];
uchar code qwe[]={ 0xc0,0xf9,0xa4,0xb0,0x99,//4
                   0x92,0x82,0xf8,0x80,0x90,//9
                   0x88,0x83,0xc6,0xa1,0x86,//14
                   0x8e,0x09,0xff,0xbf      //19
};
struct SMG_Data SMG_data[8];

/*
void duan(char x){


}

void wei(char x){

}*//*
void Get_a_value(uchar x, uchar y){
  //  a[x]=y;


}*/
void display(void){
    uchar i,w=0xfe;
    for(i=0;i<8;i++){
        /*if(i==2){
            Duan=(qwe[SMG_data[i].Data])&0x7f;
        } else*/
        Duan=qwe[SMG_data[i].Data];
        Wei=w;
        delay(1);
        Wei=0xff;
        w=w<<1|0x01;
    }

}
void Toki(uint x,LeveL Level,MODE Mode,STATE State){
    static uint i=0,speed=0,count=0;
    static bit Toki_flag=0,speed_flag=0;

    switch (State) {
        case Start:count++;
            break;
        case Stop:count=count;
            break;
    }
    if(Toki_flag==0){i=x;Toki_flag=1;}//时间初始值赋值，标志位置一停止

    if(Mode == reduction){
        if(count>=speed){i--;count=0;}
    }
    else {
        if(count>=speed){i++;count=0;}
    }

    switch (Level) {
        case Ms:speed=10;
            break;

        case s:speed=90;
            break;

        case Min:speed=90*60;
            break;

        case Hour:speed_flag=1;
            break;
    }

/*
    SMG_data[5].Data = i%10;
    SMG_data[4].Data = i/10%10;
    SMG_data[2].Data = i/100%10;
    SMG_data[1].Data = i/1000%10;
*/
    Display_DATA(i/1000%10,i/100%10,i/10%10,i%10);
}

void Display_DATA( uchar a0, uchar a1,uchar a2,uchar a3){
    SMG_data[5].Data = a3 ;
    SMG_data[4].Data = a2 ;
    SMG_data[2].Data = a1 ;
    SMG_data[1].Data = a0 ;
    display();
}


//段码列表
uchar code list[]={
    0xfe,0xfe,0xfe,0xfe,
    0xfd,0xfb,
    0xf7,0xf7,0xf7,0xf7,
    0xef,0xdf
};
//位码列表
uchar code bit_list[]={
        0,1,2,3,
        3,3,
        3,2,1,0,
        0,0
};

//圆形环绕，数码管选择设置
//n：位选
//Data：段码数据
void circle_SMG_setPort(uchar n,uchar Data){
    Wei=0xff;
    switch (n) {
        case 0:Wei=Wei&0xfd;
            break;
        case 1:Wei=Wei&0xfb;
            break;
        case 2:Wei=Wei&0xef;
            break;
        case 3:Wei=Wei&0xdf;
            break;
    }
    Duan=Data;
}

//数码管环绕显示，
//n：位数
void circle_SMG(uchar n,uint Delay){
    uchar i=0,m,j;
    while(i<12){
        m=Delay/n;
        while(m--){
            for (j = 0; j < n ; j++) {
                circle_SMG_setPort( bit_list[ ( i + j ) %12 ],list[ ( i + j ) %12 ]);
                delay(1);
            }
        }
        i++;
    }

}

