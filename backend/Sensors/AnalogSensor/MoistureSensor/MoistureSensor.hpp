#ifndef MOISTRESENSOR_H
#define MOISTRESENSOR_H

#include "../../Sensor.h"
#include "./../../ADC.hpp"
#include "iostream"
#include "./../AnalogSensor.hpp"
#include <bcm2835.h>

class MoistureSensor: AnalogSensor, Sensor{

public:
    MoistureSensor(int intervall, uint8_t channel, int id, ADC*);

    bool getEvent(sensors_event_t*);
    void getSensor(sensor_analog_t*);

    float readMoisture();


private:

    ADC* _ADC;
    uint8_t _channel;
    int _id;
};


#endif
