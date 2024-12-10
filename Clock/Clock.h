#ifndef __CLOCK_H_
#define __CLOCK_H_


void Clock_Init();
void display_time();
void display_alarm_time();
void update_time();

void Menu0();
void Menu_SetTime();
void Menu_SetAlarm();

void ClockMainSystem();

extern unsigned char index;//页面指针
extern char hours, minutes, seconds; // 当前时间
extern char alarm_hour, alarm_minute; // 闹钟时间

#endif