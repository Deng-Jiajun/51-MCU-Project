#ifndef _IIC_H_
#define _IIC_H_

// 应答（继续发送）Acknowledgement
#define ACK 0

// 非应答（停止发送）Negative Acknowledgement
#define NACK 1

/* 单片机引脚实现 IIC协议 */
sbit SCL = P1 ^ 0; // 时钟线
sbit SDA = P1 ^ 1; // 数据线

/**
 * @brief IIC 延时 5μs
 *
 */
void IIC_Dealy(void);

/**
 * @brief IIC 主机发出起始信号 S
 *
 */
void IIC_Start(void);

/**
 * @brief IIC 主机发出中止信号 P
 *
 */
void IIC_End(void);

/**
 * @brief IIC 主机发送应答
 *
 * @param ask 应答：ACK；非应答：NACK
 */
void IIC_Send_ACK(bit ask);

/**
 * @brief IIC 主机检查从机应答（接收数据）
 *
 * @return bit 应答：ACK；非应答：NACK
 */
bit IIC_Check_ACK(void);

/**
 * @brief IIC 主机发送字符（字节）
 *
 * @param c 要发送的字符
 */
void IIC_Send_Byte(unsigned char c);

/**
 * @brief IIC 主机接收字符（字节）
 *
 * @return unsigned char 接收到的字节
 */
unsigned char IIC_Read_Byte(void);

#endif