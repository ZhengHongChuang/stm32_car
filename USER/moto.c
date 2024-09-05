/*
 * @Descripttion: Leetcode_code
 * @version: 1.0
 * @Author: zhc
 * @Date: 2024-09-04 09:27:35
 * @LastEditors: zhc
 * @LastEditTime: 2024-09-05 15:53:23
 */

#include "moto.h"

/*
M1+ PB8
M1- PB9

M2+ PB6
M2- PB7
*/
void Moto_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /* Configure PB5---PB9 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5| GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void Car_Forward(void)
{
    
    GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_SET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_SET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_RESET);
}
void Car_Back(void)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_SET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_SET);
}
void Car_Left(void)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_SET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_SET);
}
void Car_Right(void)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_SET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_SET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_RESET);
}
void Car_Stop(void)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_RESET);
}

