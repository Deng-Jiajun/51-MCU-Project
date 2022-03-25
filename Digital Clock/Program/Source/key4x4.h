#ifndef _KEY4X4_H_
#define _KEY4X4_H_

#define KEY_PORT P3


/**
 * @brief 检测按键事件
 * 
 * @return unsigned char 对应位置 1~16，未按下返回0
 */
unsigned char KeyScan(void);

/**
 * @brief 建立按键位置和按键含义的映射
 * 
 * @return unsigned char 按键对应的字符
 */
unsigned char KeyValue(void);
#endif