#include <reg51.h>
#include "delay.h"
#include "lcd1602.h"
#include "key.h"

/**
 * 第一行显示 AbCd@123.com
 * 第二行显示 a=10 b=20
 * 按键1按下a+1
 * 按键2按下a-1
 * 按键3按下b+5
 * 按键4按下b-5
 *
 */
void main(void)
{
    unsigned int a = 10, b = 20;

    LCD1602_Init();
    LCD1602_string(0, 0, "AbCd@123.com");
    LCD1602_string(1, 0, "a=10 b=20");
    while (1)
    {
        // 实验发现，只要while循环里有延时，lcd1602 就会屏闪，按键检测也失效，这部分内容先搁置
        if (KEY1 == 0)
        {
            DelayXms(10);
            if (KEY1 == 0){
                LCD1602_2num(1,12,99);
            }
        }
    }
}
