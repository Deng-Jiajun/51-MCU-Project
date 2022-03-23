#include <reg51.h>
#include "delay.h"
#include "uart.h"

/*
MODE COM1 9600,0,8,1
ASSIGN COM1<SIN>SOUT
*/

void main(void)
{
  /*
  1.单片机上电后发送「ABCD 1234」到串口助手并换行。
  2.串口助手发送「O」给单片机，单片机接收后点亮 LED0，
    串口助手发送「F」给单片机，单片机接收后关闭 LED0
  3.串口助手发送「T」给单片机，单片机接收后点亮 LED2
  4.串口助手发送「LETTER」给单片机，单片机接收后发送「姓名首字母+学号」到串口助手并换行
  5.串口助手发送「ALL_ON」给单片机，单片机接收后点亮所有 LED，并发送「ALL_ON」回串口助手
  6.串口助手发送「ALL_OFF」给单片机，单片机接收后关闭所有 LED，并发送「ALL_OFF」回串口助手
  */

  // 串口通信初始化
  UartInit();

  // 测试发送
  UartSendByte('0');
  UartSendString("1234567");
  while (1)
  {

    // 试了一天，发现串口中断的触发有点问题，向串口发送内容基本是正常的


    // if (RI) // 接收中断，Receive Interrupt
    // {
    //   UartSendString("RI");
    //   RI = 0; // 清标志位（必须软件清零）
    // }
    // // 点亮 LED1~LED4
    // TurnOnLED(0);
    // TurnOnLED(1);
    // TurnOnLED(2);
    // TurnOnLED(3);
  }
}
