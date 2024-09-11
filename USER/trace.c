/*
 * @Descripttion: Leetcode_code
 * @version: 1.0
 * @Author: zhc
 * @Date: 2024-09-10 16:18:47
 * @LastEditors: zhc
 * @LastEditTime: 2024-09-11 15:24:40
 */
#include "trace.h"

/*
实现小车的避障功能，正常直行，
遇到障碍物就停下检测，检测左右两边，
哪边没有障碍物就往哪边转，两边都没有默认右转，
两边都有障碍物时后退一定的距离，然后重新检测左右两边
*/
uint32_t distance;
uint32_t lef_distance;
uint32_t right_distance;
void trace(void)
{
    
    // TIM_SetCompare4(TIM3, 15); // 正常工作状态
    // delay_ms(250);
    // distance = uw_distance(); // 前方距离
    // printf("distance %d\n", distance);
    // delay_ms(250);

    // TIM_SetCompare4(TIM3, 5); // 调整转向检测
    // delay_ms(250);
    // right_distance = uw_distance(); // 右侧距离
    // printf("right_distance %d\n", right_distance);
    // delay_ms(250);

    // TIM_SetCompare4(TIM3, 25); // 调整转向检测
    // delay_ms(250);
    // lef_distance = uw_distance(); // 左侧距离
    // printf("lef_distance %d\n", lef_distance);
    // delay_ms(250);

}
