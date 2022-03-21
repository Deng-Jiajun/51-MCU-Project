#include <reg51.h>
#include "timer.h"
#include "led.h"
#include "delay.h"

/* 方式 0 定时器只有 13 位，最大值 8191，最多只能定时 8.192ms，所以引入一个 count 计算中断的次数，以中断次数来实现更大的触发执行间隔（count ms）*/
unsigned int COUNT_T0_LED0 = 0;
unsigned int COUNT_T0_LED1 = 0;
unsigned int COUNT_T1_LED3 = 0;
unsigned int COUNT_T1_LED4 = 0;

// 间隔时间 100(ms)、200(ms)、400(ms)、1000(ms)
unsigned int INTERVAL_TIME[4] = {100, 200, 400, 1000};

unsigned char FLASH_MODE = 0;

// 初始化定时器 T0
void Init_T0(void)
{
    /* 配置定时器 */

    TMOD = TMOD & 0xF0; // 方式 0（13 位定时器）、定时模式、无需门控制
                        //（低 4 位全置 0）

    TR0 = 1; // 开启定时器 0

    // 1000μs = 1ms，2^13 = 8192，2^5 = 32
    TH0 = (8192 - 1000) / 32; // 赋值初值高 8 位
    TL0 = (8192 - 1000) % 32; // 赋值初值低 5 位

    TF0 = 0; // 清标志位

    /* 配置中断1 */
    ET0 = 1; // 允许定时器 0 中断
    EA = 1;  // 打开总中断
    PT0 = 0; // 配置优先级，低
}

// 初始化定时器 T1
void Init_T1(void)
{
    /* 配置定时器 */

    TMOD = TMOD & 0x0F; // 方式 0（13 位定时器）、定时模式、无需门控制
                        //（高 4 位全置 0）

    TR1 = 1; // 开启定时器 1

    // 1000μs = 1ms，2^13 = 8192，2^5 = 32
    TH1 = (8192 - 1000) / 32; // 赋值初值高 8 位
    TL1 = (8192 - 1000) % 32; // 赋值初值低 5 位

    TF1 = 0; // 清标志位

    /* 配置中断3 */
    ET1 = 1; // 允许定时器 0 中断
    EA = 1;  // 打开总中断
    PT1 = 0; // 配置优先级，低
}

// 定时器 T0 中断处理程序（中断向量 1）
void T0_IRQHandler(void) interrupt 1
{
    // 再次初始化
    TH0 = (8192 - 1000) / 32;
    TL0 = (8192 - 1000) % 32;

    COUNT_T0_LED0++;

    // 每 10ms 跑一次
    if (COUNT_T0_LED0 == 10)
    {
        COUNT_T0_LED0 = 0;
        // LED0 每 20ms 亮（10ms）灭（10ms）一次
        SwitchLED(0);
    }

    // LED1 每秒闪烁一次
    COUNT_T0_LED1++;

    // 每 1s(1000ms) 跑一次
    if (COUNT_T0_LED1 == 1000)
    {
        COUNT_T0_LED1 = 0;

        TurnOnLED(1);
    }
    // 闪烁太快看不出来，亮100ms再关
    if (COUNT_T0_LED1 == 100)
    {
        TurnOffLED(1);
    }
}

// 定时器 T1 中断处理程序（中断向量 3）
void T1_IRQHandler(void) interrupt 3
{
    // 再次初始化
    TH1 = (8192 - 1000) / 32;
    TL1 = (8192 - 1000) % 32;

    // LED3 每秒闪烁一次
    COUNT_T1_LED3++;

    // 每 1s(1000ms) 跑一次
    if (COUNT_T1_LED3 == 1000)
    {
        COUNT_T1_LED3 = 0;
        TurnOnLED(3);
    }
    // 闪烁太快看不出来，亮100ms再关
    if (COUNT_T1_LED3 == 100)
    {
        TurnOffLED(3);
    }

    // 通过外部中断识别按键操作，切换4种闪烁模式

    COUNT_T1_LED4++;
    if (COUNT_T1_LED4 == INTERVAL_TIME[FLASH_MODE])
    {
        COUNT_T1_LED4 = 0;
        TurnOnLED(4);
    }
    // 闪烁太快看不出来，亮100ms再关（默认MODE时，LED4会常亮)
    if (COUNT_T1_LED4 == 100)
    {
        TurnOffLED(4);
    }
}