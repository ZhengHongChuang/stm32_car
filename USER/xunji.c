/*
 * @Descripttion: Leetcode_code
 * @version: 1.0
 * @Author: zhc
 * @Date: 2024-09-11 09:09:18
 * @LastEditors: zhc
 * @LastEditTime: 2024-09-11 11:18:57
 */
#include "xunji.h"



/*
四路循迹
X1：PB15   1
X2：PB14   2 
X3：PB13   3 
X4：PA12   4
 */

void xunji_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;//定义一个结构体变量
    //打开GPIOB组引脚的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
    //初始化引脚
    //初始化PB15、PB14、PB13、PA12为输入
    GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void xunji_run(void)
{
    // Read sensor values
    uint8_t x1 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15); // Right
    uint8_t x2 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14); // Middle left
    uint8_t x3 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13); // Middle right
    uint8_t x4 = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12); // Left
    
    // Line-tracking logic
    if (x1 == 0 && x2 == 1 && x3 == 1&& x4 == 0)
    {
        Car_Forward_Speed(85); 
        
    }
    else if (x1 == 1 && x2 == 0 && x3 == 1 && x4 == 1)
    {
        Car_Right_Speed(85); 
    }
    else if (x1 == 1 && x2 == 1 && x3 == 0 && x4 == 1) 
    {
        Car_Left_Speed(85); 
    }
    else if (x1 == 0 && x2 == 0 && x3 == 1 && x4 == 1) 
    {
        Car_Right_Speed(85);
    }
    else if (x1 == 1 && x2 == 1 && x3 == 0 && x4 == 0)
    {
        Car_Left_Speed(85);
    }
    else 
    {
        Car_Stop();
    }
    delay_ms(100);
}
