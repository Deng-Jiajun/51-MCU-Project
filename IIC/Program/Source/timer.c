#include <reg51.h>
#include "timer.h"
#include "pcf8591.h"


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

    /* 配置中断 1 */
    ET0 = 1; // 允许定时器 0 中断
    EA = 1;  // 打开总中断
    PT0 = 0; // 配置优先级，低
}

unsigned int count = 0;

// 三角波
unsigned char triangularWaves[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

// 定时器 T0（方式1） 中断处理程序（中断向量 1）
void T0_MODE1_IRQHandler(void) interrupt 1
{
    TH0 = (65536 - 1000) / 256; // 重新赋值初值
    TL0 = (65536 - 1000) % 256; // 重新赋值初值

    // 模拟波形发生器输出三角波（放大 20 倍振幅）
    IIC_Write_DAC(triangularWaves[count] * 20);

    count++;
    if (count == 20)
        count = 0;
}
