#ifndef GPIO_H
#define GPIO_H

#include "bcm2835.h"

enum GPIO {
    GPIO_7 = RPI_GPIO_P1_07, 
    GPIO_11 = RPI_GPIO_P1_11, 
    GPIO_12 = RPI_GPIO_P1_12,
    GPIO_13 = RPI_V2_GPIO_P1_13,
    GPIO_15 = RPI_V2_GPIO_P1_15,
    GPIO_16 = RPI_V2_GPIO_P1_16,
    GPIO_18 = RPI_V2_GPIO_P1_18,
    GPIO_22 = RPI_V2_GPIO_P1_22
};



#endif // GPIO_H
