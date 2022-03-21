#include <reg51.h>
#include "timer.h"
#include "led.h"
#include "delay.h"

/* 方式 0 定时器只有 16 位，最大值 65535，最多只能定时 8.192ms，所以引入一个 count 计算中断的次数，以中断次数来实现更大的触发执行间隔（count ms）*/
unsigned int COUNT_T0_LED0 = 0;
unsigned int COUNT_T0_LED1 = 0;

// 间隔时间 100(ms)、200(ms)、400(ms)、1000(ms)
unsigned int INTERVAL_TIME[4] = {100, 200, 400, 1000};

// 闪烁模式，对应👆4种间隔
unsigned char FLASH_MODE = 0;

// 初始化定时器 T0（方式1）
void Init_T0_MODE1(void)
{
    /* 配置定时器 */

    TMOD &= 0xF0; //（低 4 位全置 0）
    TMOD |= 0x01; // 方式 1（16 位定时器）、定时模式、无需门控制
    TR0 = 1;      // 开启定时器 0

    // 1000μs = 1ms，2^16 = 65536，2^8 = 256
    TH0 = (65536 - 1000) / 256; // 赋值初值高 8 位（High）
    TL0 = (65536 - 1000) % 256; // 赋值初值低 8 位（Low）

    TF0 = 0; // 清标志位

    /* 配置中断1 */
    ET0 = 1; // 允许定时器 0 中断
    EA = 1;  // 打开总中断
    PT0 = 0; // 配置优先级，低
}

// 定时器 T0（方式1） 中断处理程序（中断向量 1）
void T0_MODE1_IRQHandler(void) interrupt 1
{
    // 再次初始化
    TH0 = (65536 - 1000) / 256;
    TL0 = (65536 - 1000) % 256;

    COUNT_T0_LED0++;

    // 每 1s（1000ms） 闪烁一次
    if (COUNT_T0_LED0 == 1000)
    {
        COUNT_T0_LED0 = 0; // 计数归0

        TurnOnLED(0);
    }
    // 亮100ms再关
    if (COUNT_T0_LED0 == 100)
    {
        TurnOffLED(0);
    }

    // 通过外部中断识别按键操作，切换4种闪烁模式
    COUNT_T0_LED1++;
    if (COUNT_T0_LED1 == INTERVAL_TIME[FLASH_MODE])
    {
        COUNT_T0_LED1 = 0;
        TurnOnLED(1);
    }
    // 亮100ms再关（默认MODE时，LED1会常亮)
    if (COUNT_T0_LED1 == 100)
    {
        TurnOffLED(1);
    }
}

