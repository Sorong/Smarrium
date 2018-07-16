#include "clocksensor.h"

ClockSensor::ClockSensor() : VirtualSensor(CLOCK_RESOLUTION)
{
    this->name = "Uhr";
}

bool ClockSensor::getEvent(sensors_event_t *event){


    memset(event, 0, sizeof(sensors_event_t));

    event->version   = sizeof(sensors_event_t);
    event->sensor_id = _id;
    event->type      = SENSOR_TYPE_CLOCK;
    event->timestamp = QTime::currentTime();

    if (event->light == 65536) {
        return false;
    }
    return true;
}

sensors_type_t ClockSensor::getType() const{
    return SENSOR_TYPE_CLOCK;
}

QString ClockSensor::getSort(){
    return "Clock";
}

SensorBaseType ClockSensor::getRawType(){
    return SensorBaseType::CLOCK;
}
