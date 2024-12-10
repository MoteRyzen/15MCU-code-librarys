//
// Created by mote on 2024/11/4.
//

#ifndef DEFAULT_INIT_CONFIG_H
#define DEFAULT_INIT_CONFIG_H

typedef unsigned char BYTE;
typedef unsigned int WORD; 
#define uint unsigned int
#define uchar unsigned char
//-----------------------------------------------
#define Set_time 1000//us
#define FOSC 12.//Mhz

#define T1MS ((WORD)(65536-Set_time*FOSC))      //1T模式
//#define T1MS (65536-FOSC/12/1000) //12T模式

//-----------------------------------------------



void Timer0_Init();/*
void Timer1_Init();
void Exter_INT0_Init();
void RE_INT_FRE(uint *p);

void Count_fre();*/
void getvalue( char *i);

//void Set_Parameters(uint Change_Range,uint SetLowState);



#endif //DEFAULT_INIT_CONFIG_H
