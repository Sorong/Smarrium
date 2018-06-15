#ifndef BCMINTERFACE_H
#define BCMINTERFACE_H

#if _WIN32
#include "stub/bcm2835.h"
#else
#include "bcm2835.h"
#endif
#include <cstdio>
#include <string.h>


class Bcm2835Interface{

public:

    Bcm2835Interface();
    uint8_t read8(uint8_t address, uint8_t reg);
    uint16_t read16(uint8_t address, uint8_t reg);

    void write8(uint8_t address, uint8_t value, uint8_t reg);

    uint8_t readBit(uint8_t pin);
    uint8_t readByte(uint8_t pin);

    void writeBit(uint8_t pin,int b);
    void writeByte(uint8_t pin, uint8_t byte);
};


#endif
