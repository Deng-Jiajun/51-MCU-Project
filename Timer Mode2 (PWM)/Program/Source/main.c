#include <reg51.h>
#include "delay.h"
#include "led.h"
#include "timer.h"
#include "ExternalInterrupt.h"

void main(void)
{
  /**
   * 1.使用定时器 0，方式 2
   *   控制 LED0 实现呼吸灯功能，即灯从暗变到亮，再从亮变到暗。
   *
   * 2.使用定时器 1，方式 2
   *   按键控制调节 LED1 的亮度。按下第一次亮度为 20%，再按一次，亮度为 50%，
   *   第三次按下，亮度为 80%，第四次按下，LED1 灭。再次按下重复之前步骤。
   */

  // 定时器初始化
  Init_T0_MODE2();
  Init_T1_MODE2();

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
