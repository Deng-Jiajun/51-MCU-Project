#ifndef _TIMER_H_
#define _TIMER_H_


/**
 * @brief 初始化定时器 T0
 * 
 * 方式 0（13 位定时器)，定时模式，无需门控制
 */
void Init_T0(void);

/**
 * @brief 初始化定时器 T1
 * 
 * 方式 0（13 位定时器)，定时模式，无需门控制
 */
void Init_T1(void);


// !中断处理程序不需要声明

#endif