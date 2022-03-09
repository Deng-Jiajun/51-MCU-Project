#include <reg51.h>

// 4 个开关
sbit KEY1 = P3 ^ 0;
sbit KEY2 = P3 ^ 1;
sbit KEY3 = P3 ^ 2;
sbit KEY4 = P3 ^ 3;

// 8 个 LED 灯
sbit LED1 = P0 ^ 0;
sbit LED2 = P0 ^ 1;
sbit LED3 = P0 ^ 2;
sbit LED4 = P0 ^ 3;
sbit LED5 = P0 ^ 4;
sbit LED6 = P0 ^ 5;
sbit LED7 = P0 ^ 6;
sbit LED8 = P0 ^ 7;

// LED 亮灭数组
unsigned char LED_DATA[8] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};

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
 * 第一个按键：按下一次，LED1 亮，再次按下，LED1 灭。
 * 第二个按键：按下一次，LED1 亮，按下第二次，LED2 亮，按下第三次，LED3 亮，
 *             按下第四次，LED4 亮，按下第五次 LED1 亮，依次往复。
 * 第三个按键：按下，所有 LED 灭。
 * 第四个按键：按下，所有 LED 亮。
 */

void Key1Function()
{
    LED1 = ~LED1; // LED 灯状态与上次的相反
}

void Key2Function()
{
    // 维护一个静态变量确定目前是第几次按下
    static unsigned char count = 0;
    P0 = LED_DATA[count];
    count = (++count) % 8;
}
void Key3Function()
{
    P0 = 0x00;
}
void Key4Function()
{
    P0 = 0xff;
}

void main(void)
{
    while (1)
    {
        // 应该可以用 switch，但是好像没什么意义
        if (KEY1 == 0)
        {
            DelayXms(10); // 延迟检测
            if (KEY1 == 0)
            {
                // 需要等待按键松开是因为如果按下的时间过长，会进入下一次循环，重复这个操作，而这和设计逻辑可能是相悖的
                while (KEY1 == 0)
                    ; // 等待按键松开（KEY1 变为 1）
                Key1Function();
            }
        }

        if (KEY2 == 0)
        {
            DelayXms(10);
            if (KEY2 == 0)
            {
                while (KEY2 == 0)
                    ;
                Key2Function();
            }
        }

        if (KEY3 == 0)
        {
            DelayXms(10);
            if (KEY3 == 0)
            {
                while (KEY3 == 0)
                    ;
                Key3Function();
            }
        }

        if (KEY4 == 0)
        {
            DelayXms(10);
            if (KEY4 == 0)
            {
                while (KEY4 == 0)
                    ;
                Key4Function();
            }
        }
    }
}