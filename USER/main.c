/*
 * @Descripttion: Leetcode_code
 * @version: 1.0
 * @Author: zhc
 * @Date: 2024-09-03 10:08:33
 * @LastEditors: zhc
 * @LastEditTime: 2024-09-06 16:49:05
 */

#include "stm32f10x.h"
#include "moto.h"
#include "delay.h"
#include "usart.h"
#include "exti.h"
// void init(void){
// 	Moto_Init();
// 	Delay_Init();
// 	USART1_Init();
// 	PWM_Init();
// 	my_exti_10_11_init();
// }

int main()
{
	// init();
	Moto_Init();
	Delay_Init();
	USART1_Init();
	// PWM_Init();
	my_exti_10_11_init();
	GPIO_WriteBit(GPIOB, GPIO_Pin_5, Bit_SET);
	while (1)
	{
		// Car_Forward_Speed(999);
		// delay_s(2);
		// Car_Forward_Speed(700);
		// delay_s(2);	
		// Car_Left_Speed(50);
		// Car_Forward();
	}
}
