#include <reg51.h>
#include "uart.h"
#include "delay.h"
#include "led.h"

unsigned char buffer; // 用于暂存从 SBUF 读出的数据
// 初始化串口通信
void UartInit(void)
{
    /* 配置串口通信 方式 1 */
    SCON = 0x50; // 方式1、允许接收、清标志位
    /* 👆等价👇
    SM0=0; SM1=1; // 方式 1
    REN=1;        // 允许接收
    TI=0; RI=0;   // 清标志位
    */
    // PCON |= 0x80; // 波特率增倍（PCON 最高位）❗12M
    ES = 1; // 允许串口中断

    /* 配置定时器 T1 方式 2 */
    TMOD &= 0x0F; //（高 4 位全置 0）
    TMOD |= 0x20; // 方式 2（8 位定时器）、定时模式、无需门控制
    TR1 = 1;      // 开启定时器 1
    // TL1 = 0xF9;   // 赋值初值 8 位（用于计数的初始值）波特率 9600❗12M
    // TH1 = 0xF9;   // 赋值初值 8 位（用于覆盖的初始值）波特率 9600❗12M
    TL1 = 0xFD; // ! 11.0592M
    TH1 = 0xFD; // ! 11.0592M
    TF1 = 0;    // 清标志位

    /* 配置定时器中断1（定时器1） */
    ET1 = 1; // 允许定时器 1 中断
    EA = 1;  // 打开总中断
    PT1 = 1; // 配置优先级，高
}

// 向串口发送一个字符
void UartSendByte(unsigned char c)
{
    SBUF = c;
    while (TI == 0) // 发送中断，Transmit Interrupt
        ;           // 等待，直到发送完成（发送完成 TI 会置 1）
    TI = 0;         // 清标志位（必须软件清零）
}

// 向串口发送一串字符串
void UartSendString(unsigned char *s)
{
    while (*s)
    {
        UartSendByte(*s++);
    }
}

unsigned char receivedByte; // 用于暂存从串口接收到的字符

// 串口中断处理程序
void UartIRQHandler(void) interrupt 4
{
    UartSendByte('x');
    // 收发测试，接收到后原样返回
    // 接收数据
        ES = 0;        // 关闭中断，不允许再接收
        RI = 0;        // 接收中断清零
        buffer = SBUF; // 读出SBUF中的数据
        P0 = buffer;   // 直接写给 P0 端口（连着8盏灯）
        ES = 1;        // 打开中断，允许继续接收
        RI = 0;

        // 发送数据
        SBUF = buffer;
        while (TI == 0) //等待发送完成（发送完成 TI 会置 1）
            ;
        TI = 0; // 发送中断清零

    // // UartSendString("UartIRQHandler\n");
    // if (RI) // 接收中断，Receive Interrupt
    // {
    //     // receivedByte = SBUF; // 读取字符

    //     // // 如果接收到「O」，点亮 LED0
    //     // if (receivedByte == 'O')
    //     // {
    //     //     TurnOnLED(0);
    //     // }
    //     // // 如果接收到「F」，关闭 LED0
    //     // if (receivedByte == 'F')
    //     // {
    //     //     TurnOffLED(0);
    //     // }

    //     // // 如果接收到「T」，点亮 LED1
    //     // if (receivedByte == 'T')
    //     // {
    //     //     TurnOnLED(1);
    //     // }

    //     // 处理完毕再清标志位
    //     RI = 0; // 清标志位（必须软件清零）
    // }
}