#ifndef ADC_H
#define ADC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>


#include <wiringPi.h>
#include <wiringPiSPI.h>

class ADC{

public:
    ADC();
    int myAnalogRead(int);

private:
    void spiSetup(int);
    void loadSpiDriver();
};


#endif