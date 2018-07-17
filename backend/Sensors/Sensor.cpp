#include "./backend/Sensors/Sensor.h"
#include <QDebug>
Sensor::Sensor(int interval)
{
    this->_id = QUuid::createUuid();
    this->_interval = interval;
    this->lastCheckedHour = -1;
    start(interval);
    connect(this, SIGNAL(timeout()), this, SLOT(intervallElapsed()));
    //eventValueLog = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f}; //TODO: Remove me
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
    qDebug() << "Intervall elapsed: " << value << "Sensor: " << this->getSort();
    int currentHour = QTime::currentTime().hour();
    if(this->lastCheckedHour < currentHour || currentHour == 0){
        qDebug() << "Logeintrag erstellt";
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

QList<qreal> Sensor::getEventValueLog(){
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


