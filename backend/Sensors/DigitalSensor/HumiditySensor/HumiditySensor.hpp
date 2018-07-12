#ifndef HUMIDITYSENSOR_H
#define HUMIDITYSENSOR_H

#include "./../../Sensor.h"
#include "./../../Bcm2835Interface.hpp"
#include "./../DigitalSensor.hpp"
#include <sys/time.h>
#include <time.h>

#define BASIS_ADDR              (0x51)
#define SENSITIVITY_ADDR_LOW    (0x0A)
#define SENSITIVITY_ADDR_HIGH   (0x0B)
#define OFFSET_ADDR_LOW         (0x0C)
#define OFFSET_ADDR_HIGH        (0x0D)




class HumiditySensor : DigitalSensor, Sensor
{

    public:
    HumiditySensor(int intervall, uint8_t pin, Bcm2835Interface *wire);
    ~HumiditySensor();

    bool getEvent(sensors_event_t*) override;
    void getDigitalSensor(sensor_digital_t*) override;
    uint8_t getPin() override;
    void setPin(uint8_t) override;


    float calculateHumidity();

    private:
    void calibrate();
    float readFrequenz();


    Bcm2835Interface* _wire;
    uint8_t _pin;
    uint16_t _offset = 0;
    uint16_t _sensitivity = 0;

};

#endif
