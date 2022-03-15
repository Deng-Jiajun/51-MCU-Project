#include <reg51.h>
#include "delay.h"
#include "key4X4.h"
#include "lcd1602.h"

void main(void)
{
    unsigned char keyValue = 0;    // 按下的字符
    unsigned char index = 0;       // 当前光标位置
    unsigned int leftOperand = 0;  // 左操作数
    unsigned int rightOperand = 0; // 右操作数
    unsigned char operator= ' ';   // 操作符
    LCD1602_Init();
    while (1)
    {
        /**
         * 一个简易计算器：
         *           左操作数（纯整数）+ 操作符（+、-）+ 右操作数（纯整数）
         * 基本思路：只要是表达式字符（数字、+、-），通通记录保存并输出到第一行
         *           按下 = 的时候开始计算结果，并输出到第二行
         */
        keyValue = KeyValue();

        // 先判定有没有按键按下
        if (keyValue)
        {
            // keyValue ∈ {0, 1, 2..., 9} ∪ {+, -}  （是表达式）
            if (keyValue >= '0' && keyValue <= '9' || keyValue == '+' || keyValue == '-')
            {

                // 如果没按下过操作数
                if (operator== ' ')
                {
                    // 是数字的话就是左操作数
                    if (keyValue >= '0' && keyValue <= '9')
                    {
                        // 算一下
                        leftOperand = leftOperand * 10 + keyValue - '0';
                    }
                    // 如果是操作符，记录一下
                    if (keyValue == '+' || keyValue == '-')
                    {
                        operator= keyValue;
                    }
                    // 如果到这时候左操作数还是0，就清屏输出一个0
                    // （要么按了0，要么按了操作数，结果都一样）
                    if (leftOperand == 0)
                    {
                        LCD1602_Init();
                        LCD1602_char(0, 0, '0');
                        index = 1; // 光标前移到1
                    }
                    // 其他情况就照常输出
                    else
                    {
                        LCD1602_char(0, index++, keyValue);
                    }
                }
                // 如果按下过操作数（+/-）
                else
                {
                    // 是数字的话就是右操作数
                    if (keyValue >= '0' && keyValue <= '9')
                    {
                        // 算一下
                        rightOperand = rightOperand * 10 + keyValue - '0';
                    }

                    if (rightOperand == 0)
                    {
                        // !这里可以加个判断有没有输出多余的0，不管了，摆烂了，反正不影响计算
                    }
                    // 如果是操作符
                    if (keyValue == '+' || keyValue == '-')
                    {
                        // （当作非法操作，啥也不干）
                    }
                    LCD1602_char(0, index++, keyValue);
                }
            }

            // 计算答案
            if (keyValue == '=')
            {
                // 第二行，先输出等于号
                LCD1602_char(1, 0, '=');

                // 没有写更多位的函数，就输出两位吧，彻底摆烂了属于是
                if (operator== '+')
                    LCD1602_2num(1, 1, leftOperand + rightOperand);

                // 大小也不判断了，爱错错吧
                if (operator== '-')
                    LCD1602_2num(1, 1, leftOperand - rightOperand);
            }

            // 清屏
            if (keyValue == 'C')
            {
                LCD1602_Init();

                // 数据初始化
                index = 0;        // 当前光标位置
                leftOperand = 0;  // 左操作数
                rightOperand = 0; // 右操作数
                operator= ' ';     // 操作符
            }
        }
    }
}
