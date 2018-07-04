#ifndef BCMINTERFACE_H
#define BCMINTERFACE_H


#include "bcm2835.h"
#include <cstdio>
#include <string.h>


class Bcm2835Interface{

public:

    Bcm2835Interface();
    uint8_t read8(uint8_t address, uint8_t reg);
    uint16_t read16(uint8_t address, uint8_t reg);
    uint16_t read16repeatedStart(uint8_t address, uint8_t reg);

    void write8(uint8_t address, uint8_t reg, uint8_t value);
    void write16(uint8_t address, uint8_t reg, uint16_t value);
    void write16repeatedStart(uint8_t address, uint8_t reg, uint16_t value);
    
    

    uint8_t readBit(uint8_t pin);
    uint8_t readByte(uint8_t pin);

    void writeBit(uint8_t pin,int b);
    void writeByte(uint8_t pin, uint8_t byte);

	uint8_t initConversation(uint8_t pin);

    uint8_t crc8 (uint8_t inCrc, uint8_t inData)
{
	uint8_t i;
	uint8_t data;
	data = inCrc ^ inData;
	for ( i = 0; i < 8; i++ )
	{
		if (( data & 0x80 ) != 0 )
		{
			data <<= 1;
			data ^= 0x07;
		}
		else
		{
			data <<= 1;
		}
	}
	return data;
}
};


#endif