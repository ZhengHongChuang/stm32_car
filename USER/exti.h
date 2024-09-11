/*
 * @Descripttion: Leetcode_code
 * @version: 1.0
 * @Author: zhc
 * @Date: 2024-09-06 09:45:33
 * @LastEditors: zhc
 * @LastEditTime: 2024-09-10 10:11:08
 */
#ifndef EXTI_H

#define EXTI_H


#include "stm32f10x.h"
#include "usart.h"
// #include "moto.h"
// #include "delay.h"
// #include "string.h"
void  my_exti_10_11_init(void);
void EXTI15_10_IRQHandler(void);




#endif