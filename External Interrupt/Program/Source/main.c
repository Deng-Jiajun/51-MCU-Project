#include <reg51.h>
#include "ExternalInterrupt.h"
#include "delay.h"
#include "led.h"

/**
 * @brief 定义一个全局变量，用来判断有没有回到主函数
 * 
 * 主函数会一直给它置1
 * 中断函数会判断它的值，如果是1
 *      中断1会点亮LED0
 *      中断2会点亮LED1
 * 
 * 如果两个连续的中断，中途回到了主函数，会同时点亮两盏灯
 * 如果是连续触发的中断，至少会亮其中一盏灯
 * ! 实验结果：一盏也没亮 ❓给我整不会了……
 * 分别触发都符合预期，不冲突亮两盏，冲突亮一盏
 * 问题在于，唯二的 将 FLAG_RETURN_MAIN 置 0 的语句是在亮灯后执行的，也就是从代码逻辑上看，不应该存在一盏灯都不亮的情况，暂时只能解释为冲突引发未知行为，但不知道是由于机制引发的，还是仿真软件引发的
 */
unsigned char FLAG_RETURN_MAIN;


// 单盏亮灭测试函数
void TestLED(void)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        TurnOnLED(i);
        DelayXms(200);
    }

    DelayXms(500);

    for (i = 0; i < 8; i++)
    {
        TurnOffLED(i);
        DelayXms(200);
    }
}
void main(void)
{
    /*
    外部中断实验

    设计要求
    1. 绘制仿真图，按键 1 接 P32，按键 2 接 P33
    2. 设置中断 0 为低优先级，中断 1 为高优先级
    3. 主程序点亮 LED1-LED4.
    4. 按键 1 按下关闭 LED1-LED4，并且点亮 LED5-LED6，持续大概 800ms 后关闭。
    5. 按键 2 按下点亮 LED7-LED8，持续大概 800ms 后关闭。
    测试：
    1. 按下按键 1，等待一段时间后（1s）按下按键 2
    2. 按下按键 1 后立马按下按键 2
    3. 按下按键 2 后立马按下按键 1

    实验结果：
    1. 1-4 暗，5-6 亮 800ms 后暗，1-4 亮, 7-8 亮 800ms 后暗
      （未冲突，中断分别正常响应）

    2. 1-4 暗，5-6 亮，7-8 亮 800ms 后暗，<800ms 后 5-6 暗，1-4 亮
      （冲突，高优先级插入，中断嵌套执行完毕后低优先级继续执行）

    3. 7-8 亮 800ms 后暗，1-4 暗，5-6 亮 800ms 后暗，1-4 亮
      （冲突，低优先级等待高优先级执行完毕后执行）
     */

    // TestLED();

    // 中断初始化
    Init_INT0();
    Init_INT1();

    // FLAG_RETURN_MAIN=0;

    while (1)
    {
        FLAG_RETURN_MAIN = 1;
        // // 点亮 LED1~LED4
        // TurnOnLED(0);
        // TurnOnLED(1);
        // TurnOnLED(2);
        TurnOnLED(3);
    }
}
