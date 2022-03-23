#include <reg51.h>
#include "timer.h"
#include "led.h"
#include "delay.h"

/* 方式 0 定时器只有 16 位，最大值 65535，最多只能定时 8.192ms，所以引入一个 count 计算中断的次数，以中断次数来实现更大的触发执行间隔（count ms）*/
unsigned int COUNT_T0_LED0 = 0;
unsigned int COUNT_T1_LED1 = 0;

// 闪烁模式（对应 LED1 的占空比：0%、20%、50%、80%）
unsigned char FLASH_MODE = 0;
unsigned char DUTY_CYCLE_LED1[4] = {0, 20, 50, 80};

// LED0 的占空比 [0,100]
unsigned char DUTY_CYCLE = 0;

// 占空比是否应递增
unsigned char DUTY_CYCLE_INCREASE = 1;

// 初始化定时器 T0（方式2）
void Init_T0_MODE2(void)
{
    /* 配置定时器 */
    TMOD &= 0xF0; //（低 4 位全置 0）
    TMOD |= 0x02; // 方式 2（8 位定时器）、定时模式、无需门控制
    TR0 = 1;      // 开启定时器 0
    // 周期 200μs = 0.2ms，2^8 = 256 （256 - 200 = 56）
    TL0 = 56; // 赋值初值 8 位（用于计数的初始值）
    TH0 = 56; // 赋值初值 8 位（用于覆盖的初始值）
    TF0 = 0; // 清标志位

    /* 配置中断 1 */
    ET0 = 1; // 允许定时器 0 中断
    EA = 1;  // 打开总中断
    PT0 = 0; // 配置优先级，低
}

// 初始化定时器 T1（方式2）
void Init_T1_MODE2(void)
{
    /* 配置定时器 T1 */
    TMOD &= 0x0F; //（高 4 位全置 0）
    TMOD |= 0x20; // 方式 2（8 位定时器）、定时模式、无需门控制
    TR1 = 1;      // 开启定时器 1
    // 周期 200μs = 0.2ms，2^8 = 256 （256 - 200 = 56）
    TL1 = 56; // 赋值初值 8 位（用于计数的初始值）
    TH1 = 56; // 赋值初值 8 位（用于覆盖的初始值）
    TF1 = 0; // 清标志位

    /* 配置中断 3 */
    ET1 = 1; // 允许定时器 1 中断
    EA = 1;  // 打开总中断
    PT1 = 0; // 配置优先级，低
}

// 定时器 T0（方式2） 中断处理程序（中断向量 1）
void T0_MODE2_IRQHandler(void) interrupt 1
{
    /**
     * PWM 调光
     * 以 20ms 为一个周期，每0.2ms中断一次
     *
     */
    COUNT_T0_LED0++;

    // 一个周期结束（20ms）
    if (COUNT_T0_LED0 == 100)
    {
        COUNT_T0_LED0 = 0;
        TurnOffLED(0);

        // 每个周期改变一次占空比
        // 100 之前递增，到达 100 开始递减，到 0 又开始递增，以此循环
        if (DUTY_CYCLE_INCREASE == 1)
            DUTY_CYCLE++;
        if (DUTY_CYCLE_INCREASE == 0)
            DUTY_CYCLE--;

        if (DUTY_CYCLE == 100)
            DUTY_CYCLE_INCREASE = 0;
        if (DUTY_CYCLE == 0)
            DUTY_CYCLE_INCREASE = 1;
    }

    // 这个占空比写反了，超过这个值才开始亮
    if (COUNT_T0_LED0 == DUTY_CYCLE)
    {
        TurnOnLED(0);
    }
}

// 定时器 T1（方式2） 中断处理程序（中断向量 3）
void T1_MODE2_IRQHandler(void) interrupt 3
{
    COUNT_T1_LED1++;

    // 一个周期结束（20ms）
    if (COUNT_T1_LED1 == 100)
    {
        COUNT_T1_LED1 = 0;
        TurnOnLED(1);
    }

    // 如果超过占空比，关灯
    if (COUNT_T1_LED1 == DUTY_CYCLE_LED1[FLASH_MODE])
    {
        TurnOffLED(1);
    }
}
