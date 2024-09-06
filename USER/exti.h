/*
 * @Descripttion: Leetcode_code
 * @version: 1.0
 * @Author: zhc
 * @Date: 2024-09-06 09:45:33
 * @LastEditors: zhc
 * @LastEditTime: 2024-09-06 10:56:07
 */
#ifndef EXTI_H

#define EXTI_H


#include "stm32f10x.h"
#include "usart.h"
#include "moto.h"
#include "delay.h"
void  my_exti_10_11_init(void);
void EXTI15_10_IRQHandler(void);



#endif