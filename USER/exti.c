#include "exti.h"

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

void USART1_IRQHandler(void)
{
	uint16_t data;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		// 接收数据
		data = USART_ReceiveData(USART1);
		printf("data = %c\n", data);
		switch (data)
		{
		case 'G':
			// 前进
			Car_Forward_Speed(900);
			break;
		case 'H':
			// 左边
			Car_Left_Speed(900);
			break;
		case 'J':
			// 右边
			Car_Right_Speed(900);
			break;
		case 'K':
			// 后退
			Car_Back_Speed(900);
			break;
		case 'I':
			// 停止
			Car_Stop();
			break;

		default:
			break;
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}

void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line10) == SET)
    {
        // 左边
        printf("左边\n");
		// Car_Left_Speed(900);
       
        EXTI_ClearITPendingBit(EXTI_Line10);
    }

    if(EXTI_GetITStatus(EXTI_Line11) == SET)
    {
        // 右边
        printf("右边");
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);  // 等待传输完成
        // Car_Right_Speed(900);
		EXTI_ClearITPendingBit(EXTI_Line11);
    }
}




