#include <reg51.h>
#include "key4x4.h"
#include "delay.h"

// 检测按键事件，返回按键对应位置 1~16，未按下返回 0
unsigned char KeyScan(void)
{
    /**
     * 行对应 0、1、2、3
     * 列对应 4、5、6、7
     */

    // 从端口读取的按键值
    unsigned char keyValueFromPort;

    // // 按键响应所在行对应的按键值
    // unsigned char rowKeyValue[4] = {0x0E, 0x0D, 0x0B, 0x07};

    // // 按键响应所在列对应的按键值
    // unsigned char colKeyValue[4] = {0xE0, 0xD0, 0xB0, 0x70};

    // 记录探测得到的按键行值，范围[0~4]
    unsigned char row = 0;

    // 记录探测得到的按键列值，范围[0~4]
    unsigned char col = 0;

    // 等待计时器
    unsigned char waitTimer = 0;

    /**
     * ps: 这里讨论的行列都从0开始
     *
     * 行为1，列为0（0000 1111）
     * 没有按键按下时为：0000 1111(0x0F)
     * [2,3] 按下时为：0000 1011（第2行）→ 0x0B
     *          类似的，第0行：0000 1110 → 0x0E
     *                  第1行：0000 1101 → 0x0D
     *                 (第2行：0000 1011 → 0x0B)
     *                  第3行：0000 0111 → 0x07
     */
    KEY_PORT = 0x0F; // 设置探测值（探测行）

    DelayXms(1); // 延迟检测（避免直接获得探测值）
    keyValueFromPort = KEY_PORT;

    // 判断响应行
    switch (keyValueFromPort)
    {
    case 0x0E:
        row = 0;
        break;

    case 0x0D:
        row = 1;
        break;

    case 0x0B:
        row = 2;
        break;

    case 0x07:
        row = 3;
        break;

    default:
        // 不符合以上4种情况，则没有按下按键，直接返回0
        return 0;
    }

    // 继续判断响应列
    /**
     * ps: 这里讨论的行列都从0开始
     *
     * 行为0，列为1（1111 0000）
     * 没有按键按下时为：1111 0000(0xF0)
     * [2,3] 按下时为：0111 0000（第3列）→ 0x70
     *          类似的，第0列：1110 0000 → 0xE0
     *                  第1列：1101 0000 → 0xD0
     *                  第2列：1011 0000 → 0xB0
     *                 (第3列：0111 0000 → 0x70)
     */
    KEY_PORT = 0xF0; // 设置探测值（探测列）

    DelayXms(1); // 延迟检测（避免直接获得探测值）
    keyValueFromPort = KEY_PORT;
    switch (keyValueFromPort)
    {
    case 0xE0:
        col = 0;
        break;

    case 0xD0:
        col = 1;
        break;

    case 0xB0:
        col = 2;
        break;

    case 0x70:
        col = 3;
        break;

    default:
        // 有行肯定有列，没有就出错了，返回0
        return 0;
    }

    // 只要是这4种情况中的任意一种，那按键就没有松开
    while (KEY_PORT == 0xE0 || KEY_PORT == 0xD0 || KEY_PORT == 0xB0 || KEY_PORT == 0x70)
    {
        DelayXms(1);

        // 超时就跳出循环（可以实现长按效果）
        waitTimer++;
        if (waitTimer == 255)
            break;
    }

    // 行、列判断完毕，返回对应按键位置 [1,16]
    return row * 4 + col + 1;
}

// 建立按键位置和按键含义的映射，返回按键含义，没有则返回0
unsigned char KeyValue(void)
{
    unsigned char keyValue = KeyScan();
    // keyValue ∈ [0,16]
    switch (keyValue)
    {
    case 0:
        return 0; // 没有按下按键，返回 0
    case 1:
        return '1';
    case 2:
        return '2';
    case 3:
        return '3';
    case 4:
        return '+';
    case 5:
        return '4';
    case 6:
        return '5';
    case 7:
        return '6';
    case 8:
        return '-';
    case 9:
        return '7';
    case 10:
        return '8';
    case 11:
        return '9';
    case 12:
        return 'C'; // clear
    case 13:
        return '.';
    case 14:
        return '0';
    case 15:
        return '=';
    case 16:
        return 'B'; // backspace
    }
}
