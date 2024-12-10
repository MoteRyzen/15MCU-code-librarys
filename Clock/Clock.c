#include "Clock.h"
#include "key.h"
#include "Init_config.h"
#include "LCD1602.H"
#include "stc15.h"


// 设定常量
#define NORMAL_MODE 0
#define CLOCK_SETTING_MODE 1
#define ALARM_SETTING_MODE 2
#define TURN_ON 1
#define TURN_OFF 0

// 定义全局变量
unsigned char index=NORMAL_MODE;// 当前页面指针
bit AlarmState=TURN_OFF;    //闹钟开关状态

char hours = 12, minutes = 30, seconds = 0; // 当前时间
char alarm_hour = 12, alarm_minute = 31; // 闹钟时间

// 显示当前时间
void display_time() {
    // 此处调用显示函数，显示当前时间 hour:minute:second
    LcdDisplay(0, 0, "Time: %02d:%02d:%02d   ", (int)hours, (int)minutes, (int)seconds);
}

// 显示闹钟时间
void display_alarm_time() {
    // 此处调用显示函数，显示闹钟时间 alarm_hour:alarm_minute
    LcdDisplay(0, 0, "Alarm: %02d:%02d ", (int)alarm_hour, (int)alarm_minute);
}

// 更新时间（假设使用定时器来更新时间）
void update_time() {
    
    if (index==CLOCK_SETTING_MODE)
    {      
        if(seconds <0){
            seconds=59;}
        if(minutes <0 ){
            minutes=59;}
        if(hours <0 ){
            hours=23;} 
        if (seconds >= 60) {
            seconds = 0;}
        if (minutes >= 60) {
            minutes = 0;}
        if (hours >= 24) {
            hours = 0;}            
        return;
    }
    //当正常模式正常计时运算
    if (seconds >= 60) {
        seconds = 0;minutes+=1;}
    if (minutes >= 60) {
        minutes = 0;hours+=1;}
    if (hours >= 24) {
        hours = 0;minutes=0;seconds=0;}     

}
//时钟系统初始化
void Clock_Init(){
    LcdInit();
    Key_Init();
    Timer0_Init();
    ET0 = 1;
    getvalue(&seconds);
    index=NORMAL_MODE;
}

//首页  index=Normal_Mode
void Menu0(){
    uchar KEY_Position=0;
    display_time();
    LcdDisplay(1,0,"Set|Alarm|");
        if(AlarmState==TURN_ON)         
            LcdDisplay(1,10,"T_ ON ");         
        if(AlarmState==TURN_OFF)
            LcdDisplay(1,10,"T_ off");
    ET0 = 1;
    KEY_Position=Key_GetPosition();
    switch (KEY_Position){
        case 1:  if (Key_GetState(0) == KEY_STATE_PRESSED)index=CLOCK_SETTING_MODE;    break;
        case 2:  if (Key_GetState(1) == KEY_STATE_PRESSED)index=ALARM_SETTING_MODE;    break;
        case 3:  if (Key_GetState(2) == KEY_STATE_PRESSED)AlarmState=TURN_ON;          break;
        case 4:  if (Key_GetState(3) == KEY_STATE_PRESSED)AlarmState=TURN_OFF;         break;
    }
  
    update_time();
}

//时间设置界面  index=CLOCK_Setting_mode
void Menu_SetTime(){
    u8 KEY_Position=0,temp=0;
    static u8 Set_Sign=0;//设置位选标志
    ET0=0;//关闭计时器(可选)

    //进入页面刷新界面
    LcdDisplay(0,0,"Set:%02d:%02d:%02d ",(int)hours,(int)minutes,(int)seconds);
    LcdDisplay(1,0,"Exit|Next| + | -");

    //获取按键位置
    KEY_Position=Key_GetPosition();

    switch (KEY_Position){//对应按键功能
        case 1:  if (Key_GetState(0) == KEY_STATE_PRESSED)index=NORMAL_MODE;break;
        case 2:  if (Key_GetState(1) == KEY_STATE_PRESSED)Set_Sign+=1;break;  
        case 3:  if (Key_GetState(2) == KEY_STATE_PRESSED)temp+=1;break;
        case 4:  if (Key_GetState(3) == KEY_STATE_PRESSED)temp-=1;break;  
    }

    //设置位 选择
    if(Set_Sign>=6)Set_Sign=0;
    switch (Set_Sign%6)
    {
        case 4:seconds+=temp;LcdDisplay(0,13," 1s");break;
        case 5:seconds+=temp*10;LcdDisplay(0,13,"10s");break;
        case 2:minutes+=temp;LcdDisplay(0,13," 1m");break;
        case 3:minutes+=temp*10;LcdDisplay(0,13,"10m");break;
        case 0:hours+=temp;LcdDisplay(0,13," 1h");break;
        case 1:hours+=temp*10;LcdDisplay(0,13,"10h");break;
    }
    //更新时间(CLOCK_SETTING_MODE)状态
    update_time();
    

}


//继承 [时间设置]函数   index=Alarm_Setting_Mode
void Menu_SetAlarm(){
    u8 KEY_Position=0,temp=0;
    static u8 Alarm_Sign=0;//闹钟设置位选标志
    
    //页面初始化界面
    display_alarm_time();
    LcdDisplay(1,0,"Exit|Next| + | -");
    ET0=1;//开启计时器
    
    //获取按键位置
    KEY_Position=Key_GetPosition();
    switch (KEY_Position){//对应按键功能
        case 1:  if (Key_GetState(0) == KEY_STATE_PRESSED)index=NORMAL_MODE;    break;
        case 2:  if (Key_GetState(1) == KEY_STATE_PRESSED)Alarm_Sign+=1;break;  
        case 3:  if (Key_GetState(2) == KEY_STATE_PRESSED)temp+=1;break;
        case 4:  if (Key_GetState(3) == KEY_STATE_PRESSED)temp-=1;break; 
    }

    //闹钟设置位 选择
    if(Alarm_Sign>=4)Alarm_Sign=0;
    switch (Alarm_Sign%4)
    {
        case 1:alarm_minute+=temp;LcdDisplay(0,13," 1m");break;
        case 0:alarm_minute+=temp*10;LcdDisplay(0,13,"10m");break;
        case 2:alarm_hour+=temp;LcdDisplay(0,13," 1h");break;
        case 3:alarm_hour+=temp*10;LcdDisplay(0,13,"10h");break;
    }

    //独立闹钟设置计数运算
    if(index==ALARM_SETTING_MODE){
        if(alarm_minute <0 ){
            alarm_minute=59;}
        if(alarm_hour <0 ){
            alarm_hour=23;} 
        if (alarm_minute >= 60) {
            alarm_minute = 0;}
        if (alarm_hour >= 24) {
            alarm_hour = 0;}                   
    }
}


#define Timing 1 //分钟

//定时系统，用P0全亮代替闹钟
void Alarm_System(){
    if(AlarmState==TURN_ON){
        if(hours+minutes == alarm_hour+alarm_minute){
            P0=0x00;

            //有除了K3(开启时钟按键)其他按键按下关闭闹钟
            if(Key_GetPosition()!=0&&Key_GetPosition()!=3){
                P0=0xff;
                AlarmState=TURN_OFF;
            }
        }
        //时间超过1分钟关闭闹钟
        if((hours+minutes)-(alarm_hour+alarm_minute)==Timing)
        {
            P0=0xff;
            AlarmState=TURN_OFF;    
        }
    }
}


//主系统
void ClockMainSystem(){
    //闹钟系统
    Alarm_System();
    switch (index)//页面选择
    {
        case NORMAL_MODE:
            Menu0();
            break;
        case CLOCK_SETTING_MODE:
            Menu_SetTime();
            break;
        case ALARM_SETTING_MODE:
            Menu_SetAlarm();
            break;
    
    }
}


