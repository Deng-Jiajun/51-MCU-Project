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

// 阳极 0~9
unsigned char SEG_NUMERAL_DATA_COMMON_ANODE[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

// 某一位
unsigned char SEG_DIGIT[4] = {0xFE, 0xFD, 0xFB, 0xF7};

void CommonAnodeSegmentDisplayMPX4ShowNumber(unsigned int num)
{
    unsigned char i;
    unsigned int j[4] = {1000, 100, 10, 1};

    for (i = 0; i < 4; ++i)
    {
        // 这里用 pow 会出现奇怪的错误，单步调试了一下也没解决，暂时放弃了
        // 实际上因为位数固定，用数字和 pow，有编译优化的话，得到的应该是一样的结果
        P1 = SEG_NUMERAL_DATA_COMMON_ANODE[num / j[i] % 10];

        P2 = SEG_DIGIT[i];

        DelayXms(20);

        // 亮5毫秒，然后段码和位选码都重置
        P1 = 0xFF; // 消影
        P2 = 0xFF; // 关位
    }
}

/**
 * 默认显示 0000~9999 循环
 * 按键1 显示 1234
 * 按键2 显示 5678
 * 按键3 恢复显示 0000~9999 循环
 */

// 3 个按键
sbit KEY1 = P3 ^ 0;
sbit KEY2 = P3 ^ 1;
sbit KEY3 = P3 ^ 2;

void main(void)
{

    unsigned int num = 0;
    unsigned int count = 0;
    bit isDefault = 1; // 是否默认显示（0000~9999），没有 bool，只好用 bit

    while (1)
    {

        if (KEY1 == 0)
        {
            DelayXms(10); // 延迟检测
            if (KEY1 == 0)
            {
                // 需要等待按键松开是因为如果按下的时间过长，会进入下一次循环，重复这个操作，而这和设计逻辑可能是相悖的
                while (KEY1 == 0)
                    ;              // 等待按键松开（KEY1 变为 1）
                num = 1234;        // 显示 1234
                isDefault = 0; // 关闭默认显示
            }
        }
        if (KEY2 == 0)
        {
            DelayXms(10);
            if (KEY2 == 0)
            {
                while (KEY2 == 0)
                    ;
                num = 4567;        // 显示 4567
                isDefault = 0; // 关闭默认显示
            }
        }
        if (KEY3 == 0)
        {
            DelayXms(10);
            if (KEY3 == 0)
            {
                while (KEY3 == 0)
                    ;
                isDefault = 1; // 恢复显示0000~9999
            }
        }

        if (isDefault)
        {
            // 默认显示 0000~9999
            num = count++;

            // 超过范围时归 0；
            if (count == 10000)
                count = 0;
        }

        CommonAnodeSegmentDisplayMPX4ShowNumber(num);
    }
}