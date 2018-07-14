#ifndef TEMPERATUR_SENSOR_H
#define TEMPERATUR_SENSOR_H
#include "./../../Sensor.h"
#include "./../../Bcm2835Interface.hpp"
#include "./../DigitalSensor.hpp"


#define SEARCH_ROM      (0xF0)
#define READ_ROM        (0x33)
#define MATCH_ROM       (0x55)
#define SKIP_ROM        (0xCC)
#define ALARM_SEARCH    (0xEC)
#define CONVERT_TEMP    (0x44)
#define WRITE_SCRATCH   (0x4E)
#define READ_SCRATCH    (0xBE)
#define COPY_SCRATCH    (0x48)
#define RECALL_E2       (0xB8)
#define READ_POWER_SUP  (0xB4)



class TemperatureSensor : DigitalSensor, public Sensor{

public:
    TemperatureSensor(int intervall, uint8_t pin, Bcm2835Interface* wire);
    ~TemperatureSensor();

    bool getEvent(sensors_event_t*) override;
    void getDigitalSensor(sensor_digital_t*) override;
    uint8_t getPin() override;
    void setPin(uint8_t) override;
    float readTemperature();
    sensors_type_t getType() const override;
    QString getSort() override;

private:

    void convert();
    Bcm2835Interface* _wire;
    uint8_t _pin;
};


#endif
