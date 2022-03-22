#include <reg51.h>
#include "ExternalInterrupt.h"
#include "led.h"
#include "delay.h"
#include "timer.h"

extern unsigned char FLASH_MODE;
extern unsigned int COUNT_T1_LED1;
// 初始化外部中断0（P32下降沿触发）
void Init_INT0(void)
{
    IT0 = 1; // 触发方式，下降沿触发
    IE0 = 0; // 清标志位
    EX0 = 1; // 外部中断0的开关，开
    EA = 1;  // 中断总开关，开
    PX0 = 1; // 配置优先级，高
}

// 外部中断0处理程序（中断向量0）
void INT0_IRQHandler(void) interrupt 0
{
    // 引发了中断，说明产生了按键操作，(循环)修改闪烁模式
    FLASH_MODE = (FLASH_MODE + 1) % 4;

    // 重新开始计数
    COUNT_T1_LED1 = 0;

    // 根据 LED7 的亮灭判断中断是否触发
    SwitchLED(7);
}
