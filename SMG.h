//
// Created by mote on 2024/9/25.
//

#ifndef DEFAULT_SMG_H
#define DEFAULT_SMG_H

#define uint unsigned int
#define uchar unsigned char


#define Duan P2
#define Wei P4

typedef enum {
    us,
    Ms,
    s,
    Min,
    Hour
}LeveL;

typedef enum {
    reduction,
    addition
}MODE;

typedef enum {
    Start,
    Stop
}STATE;


struct SMG_Data{
    uchar WeiShu;
    uchar Data;
};
// 示例        SMG_data[1].Data = 7;
//          第1位数码管显示数组中第7位数据

void display(void);
//void Get_a_value(uchar x, struct SMG_Data y);
void Toki(uint x,LeveL Level,MODE Mode,STATE Stake);
void circle_SMG(uchar n,uint Delay);
void Display_DATA(uchar a0,uchar a1,uchar a2,uchar a3);


extern struct SMG_Data SMG_data[8];

#endif //DEFAULT_SMG_H
