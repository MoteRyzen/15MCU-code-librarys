#include "stc15.h"
#include <intrins.h>
#include "key.h"
#include "LCD1602.H"

#define KEY_PORT P3
#define KEY_NUM 4

// 按键状态定义
#define KEY_STATE_IDLE      0
#define KEY_STATE_PRESSED   1
#define KEY_STATE_HOLD      2
#define KEY_STATE_RELEASED  3

// 松开后停止计次并清零的阈值（单位：扫描周期）
#define ENABLE 1
#define DISABLE 0

// 按键结构体
typedef struct {
    unsigned char pin;      // 按键引脚
    unsigned char state;    // 当前状态
    unsigned char count;    // 按下次数（减少为 1 字节）
    unsigned char position; // 按键位置
    unsigned int release_timer; // 松开计时器（减少为 1 字节）
    unsigned char Save_Count_Value;
} Key;

unsigned char CleanFlag[KEY_NUM];

xdata Key keys[KEY_NUM];  // 将按键数组放到 XDATA 中

// 按键初始化函数
void Key_Init() {
    unsigned char i;
    for (i = 0; i < KEY_NUM; i++) {
        keys[i].pin = (1 << i); // 假设按键连接到P3.0-P3.3，每个按键对应P3口的不同引脚
        keys[i].state = KEY_STATE_IDLE;  // 初始状态为空闲状态
        keys[i].count = 0;   // 初始计数为0
        keys[i].position = i + 1; // 记录按键的位置（1, 2, 3, 4)
        keys[i].release_timer = 0;  // 初始化松开计时器
        keys[i].Save_Count_Value = DISABLE;
    }
}

// 获取按键状态
unsigned char Key_GetState(unsigned char index) {
    if (index < KEY_NUM) {
        return keys[index].state;  // 返回按键的当前状态（按下、空闲、保持按下、松开）
    } else {
        return KEY_STATE_IDLE; // 如果索引越界，返回空闲状态
    }
}

// 获取按键按下次数
unsigned int Key_GetCount(unsigned char index) {
    if (index < KEY_NUM) {
         if(keys[index].count != 0)     // 当没有计数清零时
            keys[index].Save_Count_Value = keys[index].count;   //获取备份值 
        return keys[index].count;  // 返回按键的按下次数
    } else {
        return 0; // 如果索引越界，返回0
    }
}

// 获取按键位置（无形参）
unsigned char Key_GetPosition() {
    unsigned char i;
    for (i = 0; i < KEY_NUM; i++) {
        if (keys[i].state == KEY_STATE_PRESSED || keys[i].state == KEY_STATE_HOLD) {
            return keys[i].position;  // 返回按下的按键位置（1, 2, 3, 4）
        }
    }
    return 0;  // 如果没有按键按下，则返回0
}

// 按键扫描函数
void Key_Scan() {
    unsigned char i;
    static unsigned char last_state[KEY_NUM] = {1, 1, 1, 1}; // 初始化为松开状态
    unsigned char current_state;

    for (i = 0; i < KEY_NUM; i++) {
        // 获取当前按键状态（高电平为松开，低电平为按下）
        current_state = (KEY_PORT & keys[i].pin) ? 1 : 0;

        if (current_state != last_state[i]) {
            // 状态变化，消抖
            _nop_(); // 消抖延时（简单的方式，可以根据需要调整）
            if ((KEY_PORT & keys[i].pin) ? 1 : 0 == current_state) {
                last_state[i] = current_state;

                if (current_state == 0) { // 按键按下
                    CleanFlag[i] = ENABLE;
                    keys[i].state = KEY_STATE_PRESSED;  // 更新按键状态为按下
                    keys[i].count++;    // 增加计数
                    keys[i].release_timer = 0; // 按下时清空松开计时器
                } else { // 按键松开
                    keys[i].state = KEY_STATE_RELEASED;  // 更新按键状态为松开
                    keys[i].release_timer = 0; // 松开时清空计时器
                }
            }
        } else {
            // 状态未变化
            if (current_state == 0) { // 按键按下并保持
                keys[i].state = KEY_STATE_HOLD; // 更新为保持按下状态
            } else { // 按键松开
                keys[i].state = KEY_STATE_IDLE; // 更新为空闲状态
            }
        }
    }
    CleanCount();

   
}
void CleanCount(){
    unsigned char j=0;
    for ( j = 0; j < 4; j++)
        {
            // 检查松开后的计时器，长时间松开后停止计次并清零
        if (keys[j].state == KEY_STATE_IDLE && CleanFlag[j] == ENABLE) {
            // release_timer: 用于计时松开后的时长，超时后清零计数
            
            keys[j].release_timer++;
            if (++keys[j].release_timer >= KEY_RELEASE_THRESHOLD) {
                keys[j].count = 0;  // 超过阈值清零计数
                CleanFlag[j] = DISABLE;   
            }
        }
        }
}

unsigned char CountSign[4]=0;
unsigned int Save_Count_Value(unsigned char index){
    if (index < KEY_NUM) {
        if(keys[index].count != 0)     // 当没有计数清零时 
            CountSign[index]=0;
        else CountSign[index]=1;

        return keys[index].Save_Count_Value;  
    } else {
        return 0; // 如果索引越界，返回0
    }
    
}