#ifndef _UART_H_
#define _UART_H_

// 通用异步收发传输器（Universal Asynchronous Receiver/Transmitter)

/**
 * @brief 初始化串口通信
 * 
 * 方式 1，允许接收
 */
void UartInit(void);

/**
 * @brief 向串口发送一个字符
 * 
 * @param c 送入的字符
 */
void UartSendByte(unsigned char c);

/**
 * @brief 向串口发送一串字符串
 * 
 * @param s 送入的字符串
 */
void UartSendString(unsigned char *s);

// !中断处理程序不需要声明

#endif