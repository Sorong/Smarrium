#ifndef UVSENSOR_H
#define UVSENSOR_H

#include "./../../Sensor.h"
#include "./../../ADC.hpp"
#include "./../AnalogSensor.hpp"

class UVSensor: AnalogSensor, public Sensor{

public:

    UVSensor(int intervall, uint8_t channel, ADC* adc);
    ~UVSensor();

    bool getEvent(sensors_event_t*) override;
    void getAnalogSensor(sensor_analog_t*) override;
    uint8_t getChannel() override;
    void setChannel(uint8_t) override;
    sensors_type_t getType() const override;
    QString getSort() override;
    SensorBaseType  getRawType() override;

private:
    float calculateUV();
    float averageAnalogRead(uint8_t pin);

    uint8_t _channel;
    ADC* _adc;


};



#endif
