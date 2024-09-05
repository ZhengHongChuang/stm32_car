
# ifndef MOTO_H
# define MOTO_H

# include "stm32f10x.h"

void Moto_Init(void);
void Car_Forward(void);
void Car_Back(void);
void Car_Left(void);
void Car_Right(void);
void Car_Stop(void);

# endif