/*
 * @Descripttion: Leetcode_code
 * @version: 1.0
 * @Author: zhc
 * @Date: 2024-09-03 10:08:33
 * @LastEditors: zhc
 * @LastEditTime: 2024-09-05 15:57:17
 */

#include "stm32f10x.h"
#include "moto.h"
#include "delay.h"
#include "usart.h"

int main()
{

	Moto_Init();

	Delay_Init();

	USART1_Init();

	GPIO_WriteBit(GPIOB, GPIO_Pin_5, Bit_SET);

	while (1)
	{

		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == 0)
		{
			printf("left:0\r\n");
			
		}
		else
		{
			printf("left: 1\r\n");
		}
		delay_ms(500);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == 0)
		{
			printf("right: 0\r\n");
		}
		else
		{
			printf("right:1\r\n");
		}
		delay_ms(500);
	}
}
