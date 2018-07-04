#include "ADC.hpp"

#define SPI_CHANNEL 0
#define CHANNEL_CONFIG 8

ADC::ADC()
{
    //this->loadSpiDriver();
    this->spiSetup(0);
}

void ADC::loadSpiDriver()
{
    if (system("gpio load spi") == -1)
    {
        fprintf (stderr, "Can't load the SPI driver: %s\n", strerror (errno)) ;
        exit (EXIT_FAILURE) ;
    }
}
 
void ADC::spiSetup (int spiChannel)
{
    if ((wiringPiSPISetup (spiChannel, 1000000)) < 0)
    {
        fprintf (stderr, "Can't open the SPI bus: %s\n", strerror (errno)) ;
        exit (EXIT_FAILURE) ;
    }
}
 
int ADC::myAnalogRead(int analogChannel)
{
    if(analogChannel<0 || analogChannel>7)
        return -1;
    unsigned char buffer[3] = {1}; // start bit
    buffer[1] = (CHANNEL_CONFIG+analogChannel) << 4;
    wiringPiSPIDataRW(SPI_CHANNEL, buffer, 3);
    return ( (buffer[1] & 3 ) << 8 ) + buffer[2]; // get last 10 bits
}