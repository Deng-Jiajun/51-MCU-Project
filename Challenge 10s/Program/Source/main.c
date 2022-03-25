#include <reg51.h>
#include "delay.h"
#include "seven_segment_display_mpx4.h"
#include "external_interrupt.h"

/**
 * 默认显示 0000~9999 循环
 * 按键1 显示 1234
 * 按键2 显示 5678
 * 按键3 恢复显示 0000~9999 循环
 */

/**
1.设计一个计时器，用数码管显示，范围：00.00-99.99
2.只有一个按键控制（中断方式），按下开始计时，再次按下停止计时，第三次
按下，复位为00.00，再次按下重复之前步骤。
 */

/**
 * @brief 数码管计时状态
 *
 * 0：默认，显示0000；1：计时，数字不断增加；2：停止，显示在当前的计数值；
 */
unsigned char clockState = 0;

void main(void)
{
    unsigned int count = 0;


    // INT0 中断初始化
    Init_INT0();

    while (1)
    {
        if (clockState == 0)
        {
            count = 0;
        }
        else if (clockState == 1)
        {
            count++;
        }

        CommonAnodeSegmentDisplayMPX4_DisplayNumber(count);
    }
}