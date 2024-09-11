#include "sg90.h"

void tim3_sg90_init(void)
{
/*---------------------------------------------------------------*/
	GPIO_InitTypeDef        GPIO_InitStructure;//����һ���ṹ�����
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef	    TIM_OCInitStruct;
	
	
/*---------------------------------------------------------------*/

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//��ʼ��PB1Ϊ����ʽ���
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;//Ĭ��ѡ��������
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;//��������ʽ���
	GPIO_Init(GPIOB, &GPIO_InitStructure);
/*----------2����ʼ����ʱ��------------------------------------------*/
	/*
		��ʼƵ�ʣ�72MHz ==�� 72 000 000Hz / 7200 = 10 000Hz  //����72 �ں�������ʱ�����㣬�����ȼ�һ��
		����Ҫ�����ڣ�20ms
		����Ҫ��Ƶ�ʣ�1s/����Ҫ������ --�� 1000 ms /20ms = 50Hz
	
		10 000Hz
		��1����100us����Ҫ��200�����ŵ�20ms
		------------------------------------
					  ��5������0.5ms ��500us��
					  ��10������1ms  ��1000us��
					  ��15������1.5ms��1500us��
					  ��20������2ms  ��2000us��
					  ��25������2.5ms��2500us��
	*/
	TIM_TimeBaseInitStruct.TIM_Period		= 200  - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler	= 7200 - 1;//Ԥ��Ƶ
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
/*------------------ͨ������--------------------------------------*/	
	TIM_OCInitStruct.TIM_OCMode		= TIM_OCMode_PWM1;//PWM1ģʽ
	TIM_OCInitStruct.TIM_OCPolarity	= TIM_OCPolarity_High;//������Ը�
	TIM_OCInitStruct.TIM_OutputState= TIM_OutputState_Enable;//ʹ��
	TIM_OCInitStruct.TIM_Pulse		= 0;//��ʼ�Ƚ�ֵ
	TIM_OC4Init(TIM3, &TIM_OCInitStruct);
	
	
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	
	TIM_Cmd(TIM3,ENABLE);
}
