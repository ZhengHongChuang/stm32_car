/*
 * @Descripttion: Leetcode_code
 * @version: 1.0
 * @Author: zhc
 * @Date: 2024-09-04 09:27:35
 * @LastEditors: zhc
 * @LastEditTime: 2024-09-06 18:42:53
 */

#include "moto.h"

/*
M1+ PB8
M1- PB9

M2+ PB6
M2- PB7
*/

void PWM_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    // 使能 GPIOB 和 TIM4 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  // TIM4 控制 PB6, PB8

    // 配置 PWM 输出引脚 PB6 和 PB8
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 配置定时器 TIM4 基本参数
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;  // 时钟分频，72MHz / 72 = 1MHz
    TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;    // PWM 频率 = 1MHz / 100 = 10kHz
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

    // 配置 PWM 模式
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  // 初始占空比为 0（停止）
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM4, &TIM_OCInitStructure);  // 配置 PB6 (M2+)
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);  // 配置 PB8 (M1+)

    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

    // 启用定时器
    TIM_ARRPreloadConfig(TIM4, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
}

// 设置电机速度（0-100%）
void Set_Motor_Speed(uint16_t percentage)
{
    uint16_t pulse;  // 提前声明变量

    if (percentage > 999)
        percentage = 999;

    // pulse = (uint16_t)(percentage * (100 - 1) / 100);  // 将百分比转换为 0-99 之间的 PWM 占空比
    TIM_SetCompare1(TIM4, percentage);  // 设置 PB6 (M2+)
    TIM_SetCompare3(TIM4, percentage);  // 设置 PB8 (M1+)
}

void Moto_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /* Configure PB5---PB9 in output push-pull mode */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 初始化 PWM
    PWM_Init();
}

void Car_Forward_Speed(uint16_t percentage)
{
    Set_Motor_Speed(percentage);  // 设置电机速度
    GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_SET);    // M1+
    GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_RESET);  // M1-
    GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_SET);    // M2+
    GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_RESET);  // M2-
}

void Car_Back_Speed(uint16_t percentage)
{
    // Set_Motor_Speed(percentage);  // 设置电机速度
    GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET);  // M1+
    GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_SET);    // M1-
    GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET);  // M2+
    GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_SET);    // M2-
}

void Car_Left_Speed(uint16_t percentage)
{
    Set_Motor_Speed(percentage);  // 设置电机速度
    GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_SET);    // M1+
    GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_RESET);  // M1-
    GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET);  // M2+
    GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_SET);    // M2-
}

void Car_Right_Speed(uint16_t percentage)
{
    Set_Motor_Speed(percentage);  // 设置电机速度
    GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET);  // M1+
    GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_SET);    // M1-
    GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_SET);    // M2+
    GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_RESET);  // M2-
}

void Car_Stop(void)
{
    Set_Motor_Speed(0);  // 停止电机
    GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_RESET);
}
