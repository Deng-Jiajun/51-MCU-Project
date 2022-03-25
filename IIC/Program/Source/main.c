#include <reg51.h>
#include "delay.h"
#include "iic.h"
#include "lcd1602.h"

void main(void)
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
