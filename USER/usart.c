/*
 * @Descripttion: Leetcode_code
 * @version: 1.0
 * @Author: zhc
 * @Date: 2024-09-05 11:21:56
 * @LastEditors: zhc
 * @LastEditTime: 2024-09-11 11:07:32
 */
#include "usart.h"
u8 modeType = 0;
u8 modeFlag = 0;

int fputc(int ch, FILE *f)
{
	/* 将Printf内容发往串口 */
	USART_SendData(USART1, (unsigned char)ch);
	//    while (!(USART1->SR & USART_FLAG_TXE));
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
		;
	return (ch);
}

void USART1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; // 定义一个结构体变量
	USART_InitTypeDef USART_InitStruct;	 // 定义一个串口的初始化结构体
	NVIC_InitTypeDef NVIC_InitStruct;

	// 打开GPIOA组引脚的时钟、复用IO的时钟、串口1的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// 将PA9初始化为复用推挽式输出。PA10初始化为浮空输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*
		2、初始化串口
	*/
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStruct);

	/*
		3、设置接收中断
	*/
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	// 4、设置中断通道(只打开通道，不改变优先级)
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	USART_Cmd(USART1, ENABLE);
}
void USART1_IRQHandler(void)
{
	uint16_t data;

	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		// 接收数据
		data = USART_ReceiveData(USART1);
		// printf("data = %c\n", data);

		switch (data)
		{
		case 'G':
			Car_Forward_Speed(75);
			modeFlag = 1;
			break;
		case 'H':
			Car_Right_Speed(75);
			modeFlag = 1;
			break;
		case 'J':
			// 右边
			Car_Left_Speed(75);
			modeFlag = 1;
			break;
		case 'K':
			// 后退
			Car_Back_Speed(75);
			modeFlag = 1;
			break;
		case 'I':
			// 停止
			Car_Stop();
			modeFlag = 1;
			break;
		case 'A':
			// 避障
			modeType = 1;
			modeFlag = 0;
			break;
		case 'B':
			// 循迹
			modeType = 2;
			modeFlag = 0;
			break;
		case 'C':
			// 跟随
			modeType = 3;
			modeFlag = 0;
			break;
		default:
			modeType = 0;
			modeFlag = 0;
		}
		
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}
