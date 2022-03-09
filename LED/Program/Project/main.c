#include <reg51.h>
// P1 连 8 个 LED
sbit LED0 = P0 ^ 0;
sbit LED1 = P0 ^ 1;
sbit LED2 = P0 ^ 2;
sbit LED3 = P0 ^ 3;
sbit LED4 = P0 ^ 4;
sbit LED5 = P0 ^ 5;
sbit LED6 = P0 ^ 6;
sbit LED7 = P0 ^ 7;

// 延迟函数
void Delay_xms(unsigned char ms) // 延时xms
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
    {
        // 完整循环完是1000次，即1ms
        for (j = 0; j < 333; j++)
            ; // 空指令
    }
}

// 逐位亮灭法
void BitByBit(void)
{
    // 陆续亮灭
    LED0 = 0;
    Delay_xms(100);
    LED0 = 1;

    LED1 = 0;
    Delay_xms(100);
    LED1 = 1;

    LED2 = 0;
    Delay_xms(100);
    LED2 = 1;

    LED3 = 0;
    Delay_xms(100);
    LED3 = 1;

    LED4 = 0;
    Delay_xms(100);
    LED4 = 1;

    LED5 = 0;
    Delay_xms(100);
    LED5 = 1;

    LED6 = 0;
    Delay_xms(100);
    LED6 = 1;

    LED7 = 0;
    Delay_xms(100);
    LED7 = 1;
}

// 数组控制法
// 对应某位 0
unsigned char LED_DATA[8] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};
void ArrayControl(void)
{
    unsigned char i;
    for (i = 0; i < 8; i++)
    {
        P0 = LED_DATA[i];
        Delay_xms(100);
    }
}

// 逐位移位法
void BitShift(void)
{
    unsigned char temp = 0xfe; // 1111 1110
    unsigned char i = 0;
    for (; i < 8; i++)
    {
        P0 = temp;
        temp = (temp << 1) + 1; // 1111 1101 （+1 是因为低位补的是 0）
        Delay_xms(100);
    }
}

void main(void)
{
    while (1)
    {
         // BitByBit();
       // ArrayControl();
        BitShift();
    }
}
