#ifndef UVSENSOR_H
#define UVSENSOR_H

#include "./../../Sensor.h"
#include "./../../ADC.hpp"
#include "./../AnalogSensor.hpp"

class UVSensor: AnalogSensor, Sensor{

    public:

    UVSensor(int intervall, uint8_t pin, uint8_t pinRef, uint32_t sensorID, ADC* adc);
    ~UVSensor();

    bool getEvent(sensors_event_t*);
    void getSensor(sensor_analog_t*);
    float calculateUV();

    private:
    float mapfloat(float x, float inMin, float inMax, float outMin, float outMax);
    float averageAnalogRead(uint8_t pin);


    uint8_t _pinUVin;
    uint8_t _pinRef;
    uint32_t _sensorID;
    ADC* _adc;


};



#endif
