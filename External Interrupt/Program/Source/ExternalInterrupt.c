#include <reg51.h>
#include "ExternalInterrupt.h"
#include "led.h"
#include "delay.h"

extern unsigned char FLAG_RETURN_MAIN;


// 初始化外部中断0（P32下降沿触发）
void Init_INT0(void)
{
    IT0 = 1; // 触发方式，下降沿触发
    IE0 = 0; // 清标志位
    EX0 = 1; // 外部中断0的开关，开
    EA = 1;  // 中断总开关，开
    PX0 = 0; // 配置优先级，低
}

// 初始化外部中断1（P33下降沿触发）
void Init_INT1(void)
{
    IT1 = 1; // 触发方式，下降沿触发
    IE1 = 0; // 清标志位
    EX1 = 1; // 外部中断1的开关，开
    EA = 1;  // 中断总开关，开
    PX1 = 1; // 配置优先级，高
}

// 外部中断0处理程序（中断向量0）
void INT0_IRQHandler(void) interrupt 0
{
    // 按键 1 按下关闭 LED1-LED4，并且点亮 LED5-LED6，持续大概 800ms 后关闭
    TurnOffLED(0);
    TurnOffLED(1);
    TurnOffLED(2);
    TurnOffLED(3);

    TurnOnLED(4);
    TurnOnLED(5);

    DelayXms(800);

    TurnOffLED(4);
    TurnOffLED(5);

    if (FLAG_RETURN_MAIN == 1)
    {
        TurnOnLED(0);
        FLAG_RETURN_MAIN = 0;
    }
		
}

// 外部中断1处理程序（中断向量2）
void INT1_IRQHandler(void) interrupt 2
{
    // 按键 2 按下点亮 LED7-LED8，持续大概 800ms 后关闭
    TurnOnLED(6);
    TurnOnLED(7);

    DelayXms(800);

    TurnOffLED(6);
    TurnOffLED(7);
    if (FLAG_RETURN_MAIN == 1)
    {
        TurnOnLED(1);
        FLAG_RETURN_MAIN = 0;
    }
}