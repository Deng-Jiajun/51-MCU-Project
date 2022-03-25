#include <reg51.h>
#include <INTRINS.H>
#include "iic.h"

// IIC 延时 5μs
void IIC_Dealy(void)
{
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}

// IIC 主机发出起始信号 S
void IIC_Start(void)
{
    SCL = 1;
    SDA = 1;
    IIC_Dealy(); // 保持 SCL 高电平、SDA 高电平至少 4.7μs

    SDA = 0;
    IIC_Dealy(); // 保持 SCL 高电平、SDA 低电平至少 4.7μs
}

// IIC 主机发出中止信号 P
void IIC_End(void)
{
    SDA = 0; // 好像是要先写 SDA=0
    SCL = 1;
    IIC_Dealy(); // 保持 SCL 高电平、SDA 低电平至少 4μs

    SDA = 1;
    IIC_Dealy(); // 保持 SCL 高电平、SDA 高电平至少 4.7μs
}

// IIC 主机发送应答（应答 ACK 0 、非应答 NACK 1）
void IIC_Send_ACK(bit ack)
{
    /* 应答或者非应答，SCL 都是 低 → 高 → 低 */

    SCL = 0; // SCL 低
    IIC_Dealy();

    /* 应答，则 SDA 为低（0）；不应答，则 SDA 为高（1）
       注意，要先让 SDA 改变，然后再让 SCL 维持在高电平 */
    if (ack == ACK)
    {
        SDA = 0;     // SDA 低，应答
        IIC_Dealy(); // 这里应该不需要维持这么久
    }
    else
    {
        SDA = 1;     // SDA 高，非应答
        IIC_Dealy(); // 这里应该不需要维持这么久
    }

    SCL = 1;     // SCL 高，它的维持期间才是真正表示 应答/非应答
                 // 即 SCL 为高电平时才表示数据有效
    IIC_Dealy(); // 维持至少 4μs
    SCL = 0;     // SCL 低，应答结束
}

// IIC 主机检查从机应答（接收数据）
bit IIC_Check_ACK(void)
{

    bit ack; //检测到的应答结果
    SCL = 0;
    IIC_Dealy(); // SCL 维持低电平一段时间再拉高
    SCL = 1;     // 进入数据有效期

    _nop_();
    _nop_(); // 稍微等待一段时间让电平稳定

    if (SDA == 0) // 应答
    {

        ack = ACK;
    }
    else //非应答
    {
        ack = NACK;
    }

    SCL = 0; // SCL 恢复低电平
    _nop_();
    _nop_(); // 稍微等待一段时间让电平稳定

    return ack;
}

// IIC 主机发送字符（字节）
void IIC_Send_Byte(unsigned char c)
{
    unsigned char i;

    // 逐位发送字符
    for (i = 0; i < 8; i++)
    {
        SCL = 0;     // 拉低 SCL 并稳定一段时间
        IIC_Dealy(); // 这里应该不需要维持这么久

        /* 字符一共 8 位，0000 0000，字符不断左移，每次都发送字符最高位 */
        SDA = (bit)(c & 0x80);
        IIC_Dealy(); // 等待 SDA 数据稳定
        c = c << 1;  // 最高位已经写入 SDA，字符左移，最高位变为下一位
                     //（最后 c 会变成 8 个 0）

        SCL = 1;     // 拉高 SCL，发送出这位数据
        IIC_Dealy(); // 再稳定一段时间
    }
    SCL = 0; // 然后拉低 SCL（最后一次循环需要拉低）
}

// IIC 主机接收字符（字节）
unsigned char IIC_Read_Byte(void)
{
    unsigned char receivedByte = 0;
    unsigned char i;

    // 逐位接收字符
    for (i = 0; i < 8; i++)
    {
        SCL = 0;     // 拉低 SCL 并稳定一段时间
        IIC_Dealy(); // 这里应该不需要维持这么久
        SCL = 1;     // 再拉高 SCL，接收一位数据

        /* 字符一共 8 位，0000 0000，每次都把 SDA 写入最低位并左移
           这里选择先字符左移，再写入当前位，好处是不用判断是不是最后一位
           以 i=0 时无实际意义的左移操作为代价，减少 8 次判断 i==7 
           和 IIC_Send_Byte 里的循环向对应，IIC_Send_Byte 是先读入再移位 */
        receivedByte <<= 1;                
        receivedByte |= (unsigned char)SDA;

        IIC_Dealy(); // 等一段时间
    }
    SCL = 0; // 然后拉低 SCL（最后一次循环需要拉低）

    return receivedByte;
    // return 'F';
}
