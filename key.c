#include "stc15.h"
#include <intrins.h>
#include "key.h"

#define KEY_PORT P3
#define KEY_NUM 4

// 长时间松开后停止计次并清零的阈值
#define KEY_RELEASE_THRESHOLD 1000  // 假设1000个扫描周期为松开阈值

// 按键结构体
typedef struct {
    unsigned char pin;      // 按键引脚，表示按键连接到P3的哪个引脚（P3.0、P3.1等）
    unsigned char state;    // 当前按键状态（空闲、按下、保持按下、松开）
    unsigned int count;     // 按下次数
    unsigned char position; // 按键位置（通常用于区分按键，如0、1、2、3等）
    unsigned int release_timer; // 松开计时器，用于长时间松开后清零计数
} Key;

__xdata Key keys[KEY_NUM];  // 将按键数组放到 XDATA 中，避免数据段溢出

// 按键初始化函数
// 无输入参数
// 初始化按键状态及计数器
void Key_Init(void) {
    unsigned char i;
    for (i = 0; i < KEY_NUM; i++) {
        keys[i].pin = (1 << i); // 假设按键连接到P3.0-P3.3，每个按键对应P3口的不同引脚
        keys[i].state = KEY_STATE_IDLE;  // 初始状态为空闲状态
        keys[i].count = 0;   // 初始计数为0
        keys[i].position = i; // 记录按键的位置（0, 1, 2, 3）
        keys[i].release_timer = 0;  // 初始化松开计时器
    }
}

// 获取按键状态函数
// index: 按键的索引（0 ~ KEY_NUM-1），表示要获取哪个按键的状态
// 返回值：按键的当前状态（空闲、按下、保持按下、松开）
unsigned char Key_GetState(unsigned char index) {
    if (index < KEY_NUM) {
        return keys[index].state;  // 返回按键的当前状态（按下、空闲、保持按下、松开）
    } else {
        return KEY_STATE_IDLE; // 如果索引越界，返回空闲状态
    }
}

// 获取按键按下次数函数
// index: 按键的索引（0 ~ KEY_NUM-1），表示要获取哪个按键的按下次数
// 返回值：该按键的按下次数
unsigned int Key_GetCount(unsigned char index) {
    if (index < KEY_NUM) {
        return keys[index].count;  // 返回按键的按下次数
    } else {
        return 0; // 如果索引越界，返回0
    }
}

// 获取按键位置函数
// index: 按键的索引（0 ~ KEY_NUM-1），表示要获取哪个按键的位置
// 返回值：该按键的位置（例如0、1、2、3等）
unsigned char Key_GetPosition(unsigned char index) {
    if (index < KEY_NUM) {
        return keys[index].position; // 返回按键的位置
    } else {
        return 0xFF; // 如果索引越界，返回无效的位置
    }
}

// 按键扫描函数
// 无输入参数
// 无返回值，该函数会更新按键的状态并计数
void Key_Scan(void) {
    unsigned char i;
    static unsigned char last_state[KEY_NUM] = {1, 1, 1, 1}; // 初始化为松开状态
    unsigned char current_state;

    for (i = 0; i < KEY_NUM; i++) {
        // current_state: 当前按键的状态，0表示按下，1表示松开
        current_state = (KEY_PORT & keys[i].pin) ? 1 : 0;  // 获取当前按键状态（高电平为松开，低电平为按下）

        if (current_state != last_state[i]) {
            // 状态变化，消抖
            _nop_(); // 消抖延时（简单的方式，可以根据需要调整）
            if ((KEY_PORT & keys[i].pin) ? 1 : 0 == current_state) {
                last_state[i] = current_state;

                if (current_state == 0) { // 按键按下
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

        // 检查松开后的计时器，长时间松开后停止计次并清零
        if (keys[i].state == KEY_STATE_RELEASED) {
            // release_timer: 用于计时松开后的时长，超时后清零计数
            if (++keys[i].release_timer >= KEY_RELEASE_THRESHOLD) {
                keys[i].count = 0;  // 超过阈值清零计数
            }
        }
    }
}
