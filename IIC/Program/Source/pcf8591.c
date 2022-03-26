#include <reg51.h>
#include "pcf8591.h"
#include "iic.h"

/**
 * @brief 控制字节（「写」地址）指明要写的设备，以及要进行「写」操作
 *
 * 1001 开头，A2=A1=A1=0，写为低电平，0
 *
 *
 */
unsigned char ADDR_WRITE = 0x90;

/**
 * @brief 控制字节（「读」地址）指明要读的设备，以及要进行「读」操作
 *
 * 1001 开头，A2=A1=A1=0，读为高电平，1
 *
 */
unsigned char ADDR_READ = 0x91;


// A/D 转换，成功返回 1，不成功返回 0，转换结果以指针形式返回 AD 值
bit IIC_Read_ADC(unsigned char controlByte, unsigned char *ad)
{
   bit result = 0; // 执行结果，默认失败

   IIC_Start();               // 起始信号
   IIC_Send_Byte(ADDR_WRITE); // 写入控制字节（写数据，指明目标设备）

   if (IIC_Check_ACK() == ACK) // 如果应答（找到了设备）
   {
      IIC_Send_Byte(controlByte |= 0x40); // 写入控制字节（向该设备说明模式）
                                          // 同时允许 D/A 输出

      if (IIC_Check_ACK() == ACK) // 如果应答
      {
         IIC_Start();                // 起始信号
         IIC_Send_Byte(ADDR_READ);   // 写入控制字节（读数据，指明目标设备）
         if (IIC_Check_ACK() == ACK) // 如果应答，可以接收数据
         {
            *ad = IIC_Read_Byte(); // 读出 AD 值，写入 ad
            IIC_Send_ACK(NACK);    // 不需要再接收了，返回非应答

            result = 1; // 成功读取
         }
      }
   }
   IIC_End(); // 结束本次传输，发出中止信号

   return result; // 返回执行结果
}

// D/A 转换，成功返回 1，不成功返回 0，ad 是要转换的 AD 值
bit IIC_Write_DAC(unsigned char ad)
{
   bit result = 0; // 执行结果，默认失败

   IIC_Start();               // 起始信号
   IIC_Send_Byte(ADDR_WRITE); // 写入控制字节（写数据，指明目标设备）

   if (IIC_Check_ACK() == ACK) // 如果应答（找到了设备）
   {
      IIC_Send_Byte(0x40); // 写入控制字节（D/A 输出）
                           //! 这里直接写 0x40 应该会干扰 IIC_Read_ADC

      if (IIC_Check_ACK() == ACK) // 如果应答
      {
         // IIC_Start();                //? 起始信号，这里好像不需要再 start
         IIC_Send_Byte(ad);          // 写入控制字节（给出 AD 值）
         if (IIC_Check_ACK() == ACK) // 如果应答，则写入成功
         {
            result = 1; // 成功写入
         }
      }
   }
   IIC_End(); // 结束本次传输，发出中止信号

   return result; // 返回执行结果
}