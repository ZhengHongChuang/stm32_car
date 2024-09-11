/*
 * @Descripttion: Leetcode_code
 * @version: 1.0
 * @Author: zhc
 * @Date: 2024-09-03 10:08:33
 * @LastEditors: zhc
 * @LastEditTime: 2024-09-11 14:56:43
 */

#include "stm32f10x.h"
#include "moto.h"
#include "delay.h"
#include "usart.h"
#include "exti.h"
#include "pwn.h"
#include "uw.h"
#include "sg90.h"
#include "trace.h"
#include "xunji.h"
#include "follow.h"

extern u8 modeType;
extern u8 modeFlag;

// extern uint32_t distance;
// extern uint32_t lef_distance;
// extern uint32_t right_distance;
uint32_t dis;
void init(void)
{
	// Moto_Init();
	time4_pwn_init();
	Delay_Init();
	USART1_Init();
	my_exti_10_11_init();
	tim3_sg90_init();
	uw_init();
	xunji_init();
}

// void follow(void){
// 	uint32_t distance = uw_distance();
// 	printf("distance %d\n",distance);
// }

int main()
{
	init();
	// uint32_t dis ;

	while (1)
	{
		// printf("test\n");
		delay_ms(500);
		if (modeFlag == 0)
		{
			switch (modeType)
			{
			case 0:
				// printf("自动选择\n");
				break;
			case 1:
				printf("避障\n");

				break;
			case 2:
				printf("循迹\n");
				xunji_run();
				break;
			case 3:
				printf("跟随\n");
				follow();
				break;
			default:
				break;
			}
		}

		// trace();
		// xunji_run();
		// printf("\ndistance %d\n",distance);
		// printf("\nlef_distance %d\n",lef_distance);
		// printf("\nright_distance %d\n",right_distance);

		// TIM_SetCompare4(TIM3,5);

		// delay_s(3);

		// TIM_SetCompare4(TIM3,15);

		// delay_s(3);

		// TIM_SetCompare4(TIM3,25);

		// delay_s(3);
		// 3位小数
		// printf("distance:%.3fcm\n",uw_distance());
		// if(endflag==1){
		// 	strncpy(newbuf,databuf,datanum);
		// 	printf("newbuf:%s\n",newbuf);
		// }
		// follow();

		// delay_ms(500);
	}
}
