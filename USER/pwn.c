/*
 * @Descripttion: Leetcode_code
 * @version: 1.0
 * @Author: zhc
 * @Date: 2024-09-09 16:15:34
 * @LastEditors: zhc
 * @LastEditTime: 2024-09-10 09:59:26
 */
#include "pwn.h"

/*TIM4
M1+ PB8 CH3
M1- PB9 CH4

M2+ PB6 CH1
M2- PB7 CH2
*/

//电机供电
void PB5_init(){
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_5);
}
void time4_pwn_init(){
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 |GPIO_Pin_7 |GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);    
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_Cmd(TIM4, ENABLE);
    PB5_init();

}

// // 小车前进
// void Car_Forward_Speed(uint16_t percentage)
// {
//     TIM_SetCompare1(TIM4, percentage);  // 设置 PB6 (M2+)
//     TIM_SetCompare2(TIM4, 0);  // 设置 PB7 (M2-)

//     TIM_SetCompare3(TIM4, percentage);  // 设置 PB8 (M1+)
//     TIM_SetCompare4(TIM4, 0);  // 设置 PB9 (M1-)
// }
// // 小车后退
// void Car_Back_Speed(uint16_t percentage)
// {
//     TIM_SetCompare1(TIM4, 0);  // 设置 PB6 (M2+)
//     TIM_SetCompare2(TIM4, percentage);  // 设置 PB7 (M2-)

//     TIM_SetCompare3(TIM4, 0);  // 设置 PB8 (M1+)
//     TIM_SetCompare4(TIM4, percentage);  // 设置 PB9 (M1-)
// }
// // 小车左转
// void Car_Left_Speed(uint16_t percentage)
// {
//     TIM_SetCompare1(TIM4, percentage);  // 设置 PB6 (M2+)
//     TIM_SetCompare2(TIM4, 0);  // 设置 PB7 (M2-)

//     TIM_SetCompare3(TIM4, 0);  // 设置 PB8 (M1+)
//     TIM_SetCompare4(TIM4, percentage);  // 设置 PB9 (M1-)
// }
// // 小车右转
// void Car_Right_Speed(uint16_t percentage)
// {
//     TIM_SetCompare1(TIM4, 0);  // 设置 PB6 (M2+)
//     TIM_SetCompare2(TIM4, percentage);  // 设置 PB7 (M2-)

//     TIM_SetCompare3(TIM4, percentage);  // 设置 PB8 (M1+)
//     TIM_SetCompare4(TIM4, 0);  // 设置 PB9 (M1-)
// }
// // 小车停止
// void Car_Stop()
// {
//     TIM_SetCompare1(TIM4, 0);  // 设置 PB6 (M2+)
//     TIM_SetCompare2(TIM4, 0);  // 设置 PB7 (M2-)

//     TIM_SetCompare3(TIM4, 0);  // 设置 PB8 (M1+)
//     TIM_SetCompare4(TIM4, 0);  // 设置 PB9 (M1-)
// }
// // 小车初始化
// void Moto_Init(void)
// {
//     time4_pwn_init();
// }


