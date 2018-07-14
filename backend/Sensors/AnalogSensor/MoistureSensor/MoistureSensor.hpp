#ifndef MOISTRESENSOR_H
#define MOISTRESENSOR_H

#include "../../Sensor.h"
#include "./../../ADC.hpp"
#include "iostream"
#include "./../AnalogSensor.hpp"
#include <bcm2835.h>
#include <QObject>


class MoistureSensor: AnalogSensor, public Sensor{

public:
    MoistureSensor(int intervall, uint8_t channel, ADC*);

    bool getEvent(sensors_event_t*) override;
    void getAnalogSensor(sensor_analog_t*) override;
    uint8_t getChannel() override;
    void setChannel(uint8_t) override;
    sensors_type_t getType() const override;
    QString getSort() override;
    QString toString() override;
    float readMoisture();



private:

    ADC* _ADC;
    uint8_t _channel;
};


#endif
