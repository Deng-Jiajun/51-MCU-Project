#include "key.h"
#include "delay.h"

// 检测当前按下的按键是第几个，没有则返回0
unsigned int Key()
{
    if (KEY1 == 0)
    {
        DelayXms(10);
        if (KEY1 == 0)
        {
            while (KEY1 == 0)
                ;
            return 1;
        }
    }
    if (KEY2 == 0)
    {
        DelayXms(10);
        if (KEY2 == 0)
        {
            while (KEY2 == 0)
                ;
            return 2;
        }
    }
    if (KEY3 == 0)
    {
        DelayXms(10);
        if (KEY3 == 0)
        {
            while (KEY3 == 0)
                ;
            return 3;
        }
    }
    if (KEY4 == 0)
    {
        DelayXms(10);
        if (KEY4 == 0)
        {
            while (KEY4 == 0)
                ;
            return 4;
        }
    }
    return 0;
}
