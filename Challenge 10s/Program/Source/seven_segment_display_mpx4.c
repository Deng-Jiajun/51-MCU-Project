#include <reg51.h>
#include "seven_segment_display_mpx4.h"
#include "delay.h"

// 共阳极 0~9 对应的段码
unsigned char SEGMENT_CODE_COMMON_ANODE[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

// 点亮某一位的位选码
unsigned char BIT_CODE[4] = {0xFE, 0xFD, 0xFB, 0xF7};

void CommonAnodeSegmentDisplayMPX4_DisplayNumber(unsigned int num)
{
    unsigned char i;
    unsigned int j[4] = {1000, 100, 10, 1};

    for (i = 0; i < 4; ++i)
    {
        // 这里用 pow 会出现奇怪的错误，单步调试了一下也没解决，暂时放弃了
        // 实际上因为位数固定，用数字和 pow，有编译优化的话，得到的应该是一样的结果
        SEGMENT_CODE_PORT = SEGMENT_CODE_COMMON_ANODE[num / j[i] % 10];

        BIT_CODE_PORT = BIT_CODE[i];

        /* 要求第二位的点始终亮起 */
        if (i == 1)
        {
            SEGMENT_CODE_PORT &= 0x7F;
        }

        DelayXms(5); // 亮 5 毫秒，然后段码和位选码都重置

        SEGMENT_CODE_PORT = 0xFF; // 消影
        BIT_CODE_PORT = 0xFF;     // 关位
    }
}