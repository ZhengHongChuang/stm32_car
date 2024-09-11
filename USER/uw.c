#include "uw.h"


/*
TRIG PB11
ECHO PB12

MAX DISTANCE 400cm
*/
void uw_init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

}
void uw_send(void){
    GPIO_SetBits(GPIOB, GPIO_Pin_11);
    delay_us(10);
    GPIO_ResetBits(GPIOB, GPIO_Pin_11);
}

uint32_t uw_get(void){
    uint32_t time = 0;
    while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0);
    while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 1){
        time++;
        if (time > 23529)
        {
            return 23529;
        }
        
        
        delay_us(1);
    }
    return time;
}
uint32_t uw_distance(void){
    uint32_t time = 0;
    uint32_t distance = 0;
    uw_send();
    time = uw_get();
    distance = time * 340 / 20000;
    return distance;
}
