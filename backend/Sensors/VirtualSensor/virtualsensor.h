#ifndef VIRTUALSENSOR_H
#define VIRTUALSENSOR_H

#include <backend/Sensors/Sensor.h>



class VirtualSensor : public Sensor
{
public:
    VirtualSensor(int interval);

    // Sensor interface
public:
    bool getEvent(sensors_event_t *) = 0;
    sensors_type_t getType() const = 0;
    QString getSort() = 0;
    SensorBaseType getRawType() =0;
};

#endif // VIRTUALSENSOR_H
