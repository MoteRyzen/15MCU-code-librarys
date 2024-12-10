#ifndef __KEY_H_
#define __KEY_H_

// 按键状态定义
#define KEY_STATE_IDLE      0  // 空闲状态
#define KEY_STATE_PRESSED   1  // 按下状态
#define KEY_STATE_HOLD      2  // 保持按下状态
#define KEY_STATE_RELEASED  3  // 松开状态

// 按键初始化函数声明
// 无输入参数
// 初始化按键的状态、计数器以及松开计时器
void Key_Init(void);

// 获取按键状态函数声明
// index: 按键的索引（0 ~ KEY_NUM-1），表示要获取哪个按键的状态
// 返回值：按键的当前状态（空闲、按下、保持按下、松开）
unsigned char Key_GetState(unsigned char index);

// 获取按键按下次数函数声明
// index: 按键的索引（0 ~ KEY_NUM-1），表示要获取哪个按键的按下次数
// 返回值：该按键的按下次数
unsigned int Key_GetCount(unsigned char index);

// 获取按键位置函数声明
// index: 按键的索引（0 ~ KEY_NUM-1），表示要获取哪个按键的位置
// 返回值：该按键的位置（例如0、1、2、3等）
unsigned char Key_GetPosition();

// 按键扫描函数声明
// 无输入参数
// 无返回值，该函数会更新按键的状态并计数
void Key_Scan(void);

// 清除计数器函数声明
// 无输入参数
// 重置所有按键的按下计数
void CleanCount(void);

unsigned int Save_Count_Value(unsigned char index);
// 保存计数的值


// 定义松开计时器的阈值，如果没有在编译时定义该值，则使用默认的1000
#ifndef KEY_RELEASE_THRESHOLD
#define KEY_RELEASE_THRESHOLD 1000  // 松开计时器的阈值，单位为扫描周期
#endif

//计数清理标志位 
//ENABLE    是开启计数清理标志位
//DISABLE   是关闭计数清零标志位
extern unsigned char CleanFlag[4];
extern unsigned char CountSign[4];


#endif
/*
// 主程序循环
void main() {
    Key_Init(); // 初始化按键
    while (1) {
        Key_Scan(); // 扫描按键状态

        // 在这里添加你的主程序代码
        // 例如：
        if (Key_GetState(0) == KEY_STATE_PRESSED) {
            // 按键0按下，做某些操作
        }
        if (Key_GetState(1) == KEY_STATE_HOLD) {
            // 按键1保持按下，做某些操作
        }
        if (Key_GetCount(2) > 5) {
            // 按键2超过5次按下，做某些操作
        }
        unsigned char pos = Key_GetPosition(3); // 获取按键3的位置
        // 根据按键位置做其他操作
    }
}*/