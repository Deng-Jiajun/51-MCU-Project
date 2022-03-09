#include <reg51.h>

// 延迟函数
void DelayXms(unsigned char ms) // 延时 xms
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
    {
        // 完整循环完是 1000 次，即 1ms
        for (j = 0; j < 333; j++)
            ; // 空指令
    }
}

/**
 * 1. 计算出共阳极和共阴数码管显示0-9对应的编码
 * 阳极：
 *      0：1100 0000 → 0xc0
 *      1：1111 1001 → 0xf9
 *       ……
 * 阴极 是阳极取反
 *
 * 2. 循环显示学号
 */

// 阳极 0~9
unsigned char SEG_NUMERAL_DATA_COMMON_ANODE[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

// 阴极 0~~9
unsigned char SEG_NUMERAL_DATA_COMMON_CATHODE[10] = {0x3F, 0x06, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void CommonAnodeSegmentDisplayShowNumber(void)
{
    unsigned char i;
    for (i = 0; i < 10; i = (++i) % 10)
    {
        P1 = SEG_NUMERAL_DATA_COMMON_ANODE[i];
        DelayXms(200);
    }
}

void CommonCathodeSegmentDisplayShowNumber(void)
{
    unsigned char i;
    for (i = 0; i < 10; i = (++i) % 10)
    {
        P1 = SEG_NUMERAL_DATA_COMMON_CATHODE[i];
        DelayXms(200);
    }
}
void main(void)
{
    while (1)
    {
    }
}