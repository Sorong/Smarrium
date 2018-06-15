#ifndef HUMIDITYSENSOR_H
#define HUMIDITYSENSOR_H

#include "backend/Sensors/Sensor.h"
#include "backend/Sensors/Bcm2835Interface.hpp"
#include <time.h>

#define BASIS_ADDR              (0x51)
#define SENSITIVITY_ADDR_LOW    (0x0A)
#define SENSITIVITY_ADDR_HIGH   (0x0B)
#define OFFSET_ADDR_LOW         (0x0C)
#define OFFSET_ADDR_HIGH        (0x0D)




class HumiditySensor : Sensor{

    public:
    HumiditySensor(int intervall, uint8_t pin, uint32_t sensorID, Bcm2835Interface *wire);
    ~HumiditySensor();

    void enableAutoRange(bool enabled);
    bool getEvent(sensors_event_t*);
    void getSensor(sensor_t*);
    float calculateHumidity();

    private:
    void calibrate();
    float readFrequenz();


    Bcm2835Interface* _wire;
    uint8_t _pin;
    uint32_t _sensorID;
    uint16_t _offset = 0;
    uint16_t _sensitivity = 0;

};

#endif
