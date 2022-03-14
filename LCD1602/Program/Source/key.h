#ifndef _KEY_H_
#define _KEY_H_

// 4 个开关
sbit KEY1 = P3 ^ 0;
sbit KEY2 = P3 ^ 1;
sbit KEY3 = P3 ^ 2;
sbit KEY4 = P3 ^ 3;

/**
 * @brief 检测当前按下的按键是第几个
 * 
 * @return unsigned int 1~4 对应4个按键，0 表示无按键按下
 */
unsigned int Key();

#endif