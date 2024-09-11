/*
 * @Descripttion: Leetcode_code
 * @version: 1.0
 * @Author: zhc
 * @Date: 2024-09-04 09:29:35
 * @LastEditors: zhc
 * @LastEditTime: 2024-09-05 18:41:51
 */

# ifndef MOTO_H
# define MOTO_H

# include "stm32f10x.h"

// void Moto_Init(void);
// void Car_Forward(void);
// void Car_Back(void);
// void Car_Left(void);
// void Car_Right(void);
// void Car_Stop(void);


// void PWM_Init(void);
void Car_Forward_Speed(uint16_t speed);
void Car_Back_Speed(uint16_t speed);
void Car_Left_Speed(uint16_t speed);
void Car_Right_Speed(uint16_t speed);
void Car_Stop(void);

# endif