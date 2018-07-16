#include "./backend/Sensors/Sensor.h"
#include <QDebug>
Sensor::Sensor(int interval)
{
    this->_id = QUuid::createUuid();
    this->_interval = interval;
    this->lastCheckedHour = QTime::currentTime().hour();
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
    qDebug() << "Intervall elapsed";
    sensors_event_t* event = new sensors_event_t();
    this->getEvent(event);
    logEvent(event);
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

void Sensor::logEvent(sensors_event_t *event){
    float value = 0;

    switch(event->type){

    case SENSOR_TYPE_IRTEMPERATURE:
        value = event->irTemperature;
        break;

    case SENSOR_TYPE_LIGHT:
        value = event->light;
        break;

    case SENSOR_TYPE_MOISTURE:
        value = event->moisture;
        break;

    case SENSOR_TYPE_RELATIVE_HUMIDITY:
        value = event->relative_humidity;
        break;

    case SENSOR_TYPE_TEMPERATURE:
        value = event->temperature;
        break;

    case SENSOR_TYPE_UV:
        value = event->uv;
        break;
    default:
        return;
    }
    int currentHour = QTime::currentTime().hour();
    if(this->lastCheckedHour < currentHour || currentHour == 0){
        if(eventValueLog.size() == 24){
            this->eventValueLog.pop_front();
            this->eventValueLog.push_back(value);
        }
        else{
            this->eventValueLog.push_back(value);
        }

        this->lastCheckedHour = currentHour;
    }
}

QList<float> Sensor::getEventValueLog(){
    return this->eventValueLog;
}

float Sensor::getLastEventValue(){
    if(this->eventValueLog.isEmpty()){
        return 0;
    }
    else{
        return this->eventValueLog.last();
    }
}


