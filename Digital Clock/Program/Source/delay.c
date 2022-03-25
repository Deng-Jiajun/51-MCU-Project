#include "delay.h"


// 延迟函数(单位 ms)
void DelayXms(unsigned int ms) // 延时 xms
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
    {
        // 完整循环完是 1000 次，即 1ms
        for (j = 0; j < 333; j++)
            ; // 空指令
    }
}

// 延迟函数(单位 s)
void DelayXs(unsigned int s) // 延时 xms
{
    unsigned int i, j;
    for (i = 0; i < s; i++)
    {
        DelayXms(1000);
    }
}