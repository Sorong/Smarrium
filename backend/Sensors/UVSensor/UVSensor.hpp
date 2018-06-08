#ifndef UVSENSOR_H
#define UVSENSOR_H

#include "./../Sensor.h"

class UVSensor: Sensor{

    public:

    UVSensor(uint8_t pin, uint8_t pinRef, uint32_t sensorID);
    ~UVSensor();

    void enableAutoRange(bool enabled);
    bool getEvent(sensors_event_t*);
    void getSensor(sensor_t*);
    float calculateUV();

    private:
    float mapfloat(float x, float inMin, float inMax, float outMin, float outMax);
    float averageAnalogRead(uint8_t pin);


    uint8_t _pinUVin;
    uint8_t _pinRef;
    uint32_t _sensorID;


};



#endif