#ifndef USART_H
#define USART_H
#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"

int fputc(int ch, FILE *f);
void USART1_Init(void);
void USART1_IRQHandler(void);

#endif