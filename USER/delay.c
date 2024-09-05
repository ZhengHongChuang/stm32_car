/*
 * @Descripttion: Leetcode_code
 * @version: 1.0
 * @Author: zhc
 * @Date: 2024-09-04 15:34:56
 * @LastEditors: zhc
 * @LastEditTime: 2024-09-04 17:14:32
 */
#include "delay.h"

void Delay_Init(void)
{
    // 设置为外部时钟源
    SysTick->CTRL &= (~SysTick_CTRL_CLKSOURCE_Msk);
}

void _Delay_nusOver(void)
{
    // 设置重装载值
    SysTick->LOAD = 184135 * 9;
    SysTick->VAL = 0x01;
    // 开启计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    // 等待计数器为0
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) && (SysTick->CTRL & SysTick_CTRL_ENABLE_Msk));
    // 关闭计数器
    SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);
}
//184135
void delay_us(uint32_t nus)
{
    while (nus > 184135)
    {
        _Delay_nusOver();
        nus -= 184135;
    }
    // 设置重装载值
    SysTick->LOAD = nus * 9;
    SysTick->VAL = 0x01;
    // 开启计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    // 等待计数器为0
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) && (SysTick->CTRL & SysTick_CTRL_ENABLE_Msk));
    // 关闭计数器
    SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);    
}
//1864
void delay_ms(uint32_t nms)
{
    while (nms--)
    {
        delay_us(1000);
    }
    
}
//1
void delay_s(uint32_t ns)
{
    while (ns--)
    {
        delay_ms(1000);
    } 
}