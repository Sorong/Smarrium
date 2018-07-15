#ifndef CLOCKSENSOR_H
#define CLOCKSENSOR_H

#include "./../virtualsensor.h"

#define CLOCK_RESOLUTION 60000
class ClockSensor : VirtualSensor
{
public:
    ClockSensor();

    bool getEvent(sensors_event_t *) override;
    sensors_type_t getType() const override;
    QString getSort() override;
    SensorBaseType getRawType() override;
};

#endif // CLOCKSENSOR_H
