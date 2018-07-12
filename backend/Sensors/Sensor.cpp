#include "./backend/Sensors/Sensor.h"

Sensor::Sensor(int intervall)
{
    this->_id = QUuid::createUuid();
    start(intervall);
    connect(this, SIGNAL(timeout()), this, SLOT(intervallElapsed()));
}

void Sensor::intervallElapsed(){
    sensors_event_t* event = new sensors_event_t();
    this->getEvent(event);
    emit newSensorEvent(event);
}
