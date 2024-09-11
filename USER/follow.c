#include "follow.h"

void follow(void)
{
    uint32_t distance;
    Car_Stop();
    delay_ms(200);
    distance = uw_distance();
    // uint32_t speed;

    if (distance < 8)
    {
        Car_Back_Speed(75); // 如果距离太近则倒退
    }
    else if (distance > 10)
    {
        // 根据距离调整车速，距离越远，车速越快

        // speed = (distance > 20) ? 80 : (distance - 8) * 4 + 30;
        Car_Forward_Speed(78);
    }
    else
    {
        Car_Stop(); // 距离刚好则停止
    }
    printf("distance %d \n", distance);

    // printf("distance %d, speed %d\n", distance, speed);

    // 延时避免频繁调整
    delay_ms(100);
}

// void follow(void) {
//     uint32_t distance;
//     uint32_t speed;

//     distance = uw_distance();
//     if (distance < 8) {
//         Car_Back_Speed(75);  // 如果距离太近则倒退
//         delay_ms(50);
//     } else if (distance == 8) {
//         Car_Stop();  // 距离刚好则停止
//     } else {
//         // 根据距离调整车速，距离越远，车速越快
//         speed = (distance > 20) ? 75 : (distance - 8) * 3 + 30;
//         Car_Forward_Speed(speed);
//         delay_ms(500);
//         Car_Stop();
//     }

//     printf("distance %d, speed %d\n", distance, speed);

//     // 延时避免频繁调整

// }
