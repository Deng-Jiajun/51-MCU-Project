#include <reg51.h>
#include "delay.h"
#include "iic.h"
#include "lcd1602.h"
#include "pcf8591.h"
#include "timer.h"
#include <math.h>

void main(void)
{

  //! 去 timer.c 看中断处理程序
  // Init_T0_MODE1(); // 初始化定时器
  float x;
  float temp;
  unsigned char i;
  while (1)
  {
    /**
     * 心形公式：
     * f(x) = ( 1 - (|x| -1)^2 )^(1/2)
     * g(x) = 1/cos(1- |x|) - 3
     *
     * f(x) + 3：
     * g(x) + 3：
     */
    x = 2.00;
    for (i = 1; i < 100; i++)
    {
      x = x - 0.02;
      temp = acos(1.0 - x) * 50.0;
      IIC_Write_DAC((unsigned char)temp);

      temp = sqrt(1 - (x - 1) * (x - 1)) + 3.0;
      temp = temp * 50.0;
      IIC_Write_DAC((unsigned char)temp);
    }

    x = 0.0;
    for (i = 1; i < 100; i++)
    {
      x = x + 0.02;
      temp = acos(1.0 - x) * 50.0;
      IIC_Write_DAC((unsigned char)temp);
      
      temp = sqrt(1 - (x - 1) * (x - 1)) + 3.0;
      temp = temp * 50.0;
      IIC_Write_DAC((unsigned char)temp);
    }

    DelayXms(100);
  }
}

/**
 * @brief 测试 IIC 通信的一个 main 函数
 *
 * 主要是把 pcf8591 检测到的 AD 值转换为它所对应的电压值
 *
 */
void old_main(void)
{
  unsigned char ad; // 从 PCF8591 得到的 AD 值
  float v0 = 0;     // AD 值对应的电压
  /* 电压计算公式：V_i=(AD/2^n)V_ref
    （其中 n 为 ADC 位数，实验中的 PCF8591 是 8bit 的，n=256）*/

  LCD1602_Init();
  LCD1602_string(0, 0, "test");

  while (1)
  {
    // 一下过程参考第三种情况（连续读写）
    IIC_Start();
    IIC_Send_Byte(0x90);        // 写入控制字节（写入地址，指明设备）
                                // 1001 开头，A2=A1=A1=0，写为低电平，0）
    if (IIC_Check_ACK() == ACK) // 如果应答（找到了设备）
    {
      IIC_Send_Byte(0x00);        // 写入控制字节（向该设备说明模式）
      if (IIC_Check_ACK() == ACK) // 如果应答
      {
        IIC_Start();
        IIC_Send_Byte(0x91);        // 读内容
                                    // 1001 开头，A2=A1=A1=0，读为高电平，1）
        if (IIC_Check_ACK() == ACK) // 如果应答，可以接收数据
        {
          ad = IIC_Read_Byte(); // 读出 AD 值
          IIC_Send_ACK(NACK);   // 不需要再接收了，返回非应答

          // AD 值转换为电压值 v0
          v0 = (ad / 256.0) * 5.0;
          v0 *= 100; // 放大100倍，方便显示

          // 用LCD1602显示
          LCD1602_2num(1, 5, (int)v0 / 100);
          LCD1602_char(1, 7, '.');
          LCD1602_2num(1, 8, (int)v0 % 100);
          LCD1602_char(1, 10, 'v');
        }
      }
    }
    IIC_End(); // 结束本次读取，发出中止信号

    DelayXms(100); // 等一会儿
  }
}
