#ifndef _PCF8591_H_
#define _PCF8591_H_

/**
 * @brief A/D 转换
 * 
 * @param controlByte 控制字符，用于模式说明
 * @param ad 保存转换得到的 AD 值
 * @return bit 成功返回 1，不成功返回 0
 */
bit IIC_Read_ADC(unsigned char controlByte, unsigned char *ad);

/**
 * @brief D/A 转换
 * 
 * @param ad 要转换的 AD 值
 * @return bit 成功返回 1，不成功返回 0
 */
bit IIC_Write_DAC(unsigned char ad);

#endif