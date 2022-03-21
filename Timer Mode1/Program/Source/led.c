#include <reg51.h>
#include "led.h"
#include "delay.h"

// LED 连到 P0 端口
#define PORT P0

// PORT 端口连 8 个 LED
sbit LED0 = PORT ^ 0;
sbit LED1 = PORT ^ 1;
sbit LED2 = PORT ^ 2;
sbit LED3 = PORT ^ 3;
sbit LED4 = PORT ^ 4;
sbit LED5 = PORT ^ 5;
sbit LED6 = PORT ^ 6;
sbit LED7 = PORT ^ 7;

// 开/关 对应序号的灯（如果亮的就关掉，如果暗的就点亮）
void SwitchLED(unsigned char index)
{
    switch (index)
    {
    case 0:
        LED0 = ~LED0;
        break;
    case 1:
        LED1 = ~LED1;
        break;
    case 2:
        LED2 = ~LED2;
        break;
    case 3:
        LED3 = ~LED3;
        break;
    case 4:
        LED4 = ~LED4;
        break;
    case 5:
        LED5 = ~LED5;
        break;
    case 6:
        LED6 = ~LED6;
        break;
    case 7:
        LED7 = ~LED7;
        break;
    }
}

// 打开对应序号的灯
void TurnOnLED(unsigned char index)
{
    switch (index)
    {
    case 0:
        LED0 = 0;
        break;
    case 1:
        LED1 = 0;
        break;
    case 2:
        LED2 = 0;
        break;
    case 3:
        LED3 = 0;
        break;
    case 4:
        LED4 = 0;
        break;
    case 5:
        LED5 = 0;
        break;
    case 6:
        LED6 = 0;
        break;
    case 7:
        LED7 = 0;
        break;
    }
}

// 关闭对应序号的灯
void TurnOffLED(unsigned char index)
{
    switch (index)
    {
    case 0:
        LED0 = 1;
        break;
    case 1:
        LED1 = 1;
        break;
    case 2:
        LED2 = 1;
        break;
    case 3:
        LED3 = 1;
        break;
    case 4:
        LED4 = 1;
        break;
    case 5:
        LED5 = 1;
        break;
    case 6:
        LED6 = 1;
        break;
    case 7:
        LED7 = 1;
        break;
    }
}

// 逐位亮灭法
void BitByBit(void)
{
    // 陆续亮灭
    LED0 = 0;
    DelayXms(100);
    LED0 = 1;

    LED1 = 0;
    DelayXms(100);
    LED1 = 1;

    LED2 = 0;
    DelayXms(100);
    LED2 = 1;

    LED3 = 0;
    DelayXms(100);
    LED3 = 1;

    LED4 = 0;
    DelayXms(100);
    LED4 = 1;

    LED5 = 0;
    DelayXms(100);
    LED5 = 1;

    LED6 = 0;
    DelayXms(100);
    LED6 = 1;

    LED7 = 0;
    DelayXms(100);
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
        PORT = LED_DATA[i];
        DelayXms(100);
    }
}

// 逐位移位法
void BitShift(void)
{
    unsigned char temp = 0xfe; // 1111 1110
    unsigned char i = 0;
    for (; i < 8; i++)
    {
        PORT = temp;
        temp = (temp << 1) + 1; // 1111 1101 （+1 是因为低位补的是 0）
        DelayXms(100);
    }
}