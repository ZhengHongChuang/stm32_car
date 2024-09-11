/*
 * @Descripttion: Leetcode_code
 * @version: 1.0
 * @Author: zhc
 * @Date: 2024-09-06 09:45:20
 * @LastEditors: zhc
 * @LastEditTime: 2024-09-11 10:26:24
 */
#include "exti.h"
// u8 modeType = 0;
void my_exti_10_11_init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;//定义一个结构体变量
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	
	//打开GPIOB组引脚的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//1、初始化引脚
	//初始化PA11和PB10为输入
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);



	
	//2、初始化外部中断
	EXTI_InitStruct.EXTI_Line	= EXTI_Line10 | EXTI_Line11;
	EXTI_InitStruct.EXTI_Mode	= EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger= EXTI_Trigger_Falling;
	EXTI_InitStruct.EXTI_LineCmd= ENABLE;
	EXTI_Init(&EXTI_InitStruct);
	
	//3、将引脚作为外部中断的输入
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource11);
	
	//4、设置中断通道(只打开通道，不改变优先级)
	NVIC_InitStruct.NVIC_IRQChannel		= EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd	= ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
}




//中断服务函数
void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line10) == SET)
    {
        // 左边
        // printf("左边\n");
		// Car_Left_Speed(900);
       
        EXTI_ClearITPendingBit(EXTI_Line10);
    }

    if(EXTI_GetITStatus(EXTI_Line11) == SET)
    {
        // 右边
        // printf("右边");
        
		EXTI_ClearITPendingBit(EXTI_Line11);
    }
}




