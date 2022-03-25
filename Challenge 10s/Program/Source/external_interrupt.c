#include <reg51.h>
#include "external_interrupt.h"
#include "delay.h"
#include "seven_segment_display_mpx4.h"

extern unsigned char clockState;

// 初始化外部中断0（P3.2下降沿触发）
void Init_INT0(void)
{
    IT0 = 1; // 触发方式，下降沿触发
    IE0 = 0; // 清标志位
    EX0 = 1; // 外部中断0的开关，开
    EA = 1;  // 中断总开关，开
    PX0 = 0; // 配置优先级，低
}

// 外部中断0处理程序（中断向量0）
void INT0_IRQHandler(void) interrupt 0
{
    // 按下开始计时，再次按下停止计时，第三次按下，复位为00.00，再次按下重复之前步骤
    clockState = ++clockState % 3;
}
