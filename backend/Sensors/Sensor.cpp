#include "./backend/Sensors/Sensor.h"

Sensor::Sensor(int interval)
{
    this->_id = QUuid::createUuid();
    this->_interval = interval;
    start(interval);
    connect(this, SIGNAL(timeout()), this, SLOT(intervallElapsed()));
}

const QString &Sensor::toString()
{
    return this->name;
}

QUuid Sensor::getUuid()
{
    return this->_id;
}

void Sensor::intervallElapsed(){
    sensors_event_t* event = new sensors_event_t();
    this->getEvent(event);
    emit newSensorEvent(event);
}

int Sensor::getInterval(){
    return this->_interval;
}


void Sensor::setInterval(int interval){
    stop();
    start(interval);
}

QString Sensor::getId(){
    return this->_id.toString();
}


