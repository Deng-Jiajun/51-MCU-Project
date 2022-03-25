#ifndef _SEVEN_SEGMENT_DISPLAY_MPX4_H_
#define _SEVEN_SEGMENT_DISPLAY_MPX4_H_

// 段码对应端口
#define SEGMENT_CODE_PORT P1

// 位码对应端口
#define BIT_CODE_PORT P2

/**
 * @brief 共阳极四位数码管显示数字
 * 
 * @param num 要显示的数字
 */
void CommonAnodeSegmentDisplayMPX4_DisplayNumber(unsigned int num);

#endif