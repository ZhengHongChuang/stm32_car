
#ifndef DELAY_H

#define DELAY_H
#include "stm32f10x.h"

void Delay_Init(void);
void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);
void delay_s(uint32_t ns);

#endif