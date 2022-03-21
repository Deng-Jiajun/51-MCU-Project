#ifndef _LED_H_
#define _LED_H_

/**
 * @brief 开/关 对应序号的灯（如果亮的就关掉，如果暗的就点亮）
 *
 * @param index 灯的序号 [0,7]
 */
void SwitchLED(unsigned char index);

/**
 * @brief 打开对应序号的灯
 *
 * @param index 灯的序号 [0,7]
 */
void TurnOnLED(unsigned char index);

/**
 * @brief 关闭对应序号的灯
 *
 * @param index 灯的序号 [0,7]
 */
void TurnOffLED(unsigned char index);

// 三个跑马灯

// ① 逐位亮灭法
void BitByBit(void);

// ② 数组控制法
void ArrayControl(void);

// ③ 逐位移位法
void BitShift(void);

#endif