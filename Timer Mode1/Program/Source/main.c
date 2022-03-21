#include <reg51.h>
#include "delay.h"
#include "led.h"
#include "timer.h"
#include "ExternalInterrupt.h"

void main(void)
{

  // 方式 0
  /**
   * 使用定时器 0，方式 0
   *    定时 1ms 中断一次，
   *    控制 LED1 灯每 20ms 亮（10ms）灭（10ms）一次，
   *    控制 LED2 每秒闪烁一次。
   *
   * 使用定时器 1，方式 0，
   *    控制 LED3 每秒闪烁一次。
   *    用一个按键控制 LED4，默认 100ms 闪烁一次，
   *        按下第一次每 200ms 闪烁一次，
   *        再按一次，400ms 闪烁一次，
   *        第三次按下，1s 闪烁一次，
   *        再次按下重复之前步骤（恢复100ms闪烁一次）。
   */

  // 定时器初始化
  Init_T0();
  Init_T1();

  // 外部中断0 初始化
  Init_INT0();

  while (1)
  {
    ;
    // // 点亮 LED1~LED4
    // TurnOnLED(0);
    // TurnOnLED(1);
    // TurnOnLED(2);
    // TurnOnLED(3);
  }
}
