#include "actuatormanager.h"
#include "backend/Actuator/Actuator.hpp"
#include <QDebug>
#include <QJsonDocument>

ActuatorManager::ActuatorManager(QObject *parent) : QObject(parent)
{
}

void ActuatorManager::registerActuator(Actuator &actuator)
{
    this->_actuator = &actuator;
}

bool ActuatorManager::registerSensor(Sensor& sensor, SensorConfig& config)
{
    this->sensorList.addUnique(&sensor);
    SensorConfig *current = this->configurations[&sensor];
    if(current) {
        delete current;
    }

    this->configurations[&sensor] = &config;
    this->sensorIds[sensor.getId()] = &sensor;
    connect(&sensor, SIGNAL(newSensorEvent(sensors_event_t*)), this, SLOT(eventReceived(sensors_event_t*)));
    return true;
}

SensorList &ActuatorManager::getSensors()
{
    return this->sensorList;
}

void ActuatorManager::eventReceived(sensors_event_t* event)
{
    qDebug() << "Event recived: " << event->timestamp;

    if(!_actuator) {
        return;
    }
    SensorConfig* config = this->configurations[sensorIds[event->sensor_id]];

    if(config->ignoreSwitches()){
        return;
    }

    float eventData = 0;
    switch(event->type){

    case SENSOR_TYPE_TEMPERATURE:
        eventData = event->temperature;
        break;

    case SENSOR_TYPE_LIGHT:
        eventData = event->light;
        break;

    case SENSOR_TYPE_RELATIVE_HUMIDITY:
        eventData = event->relative_humidity;
        break;

    case SENSOR_TYPE_UV:
        eventData = event->uv;
        break;

    case SENSOR_TYPE_IRTEMPERATURE:
        eventData = event->irTemperature;
        break;

    case SENSOR_TYPE_MOISTURE:
        eventData = event->moisture;
        break;
    }

    if (config->minIsOff()){
        if(config->getMinValue(QTime::currentTime().hour()) < eventData){
            this->_actuator->switchOff();
        }

        else if(config->getMaxValue(QTime::currentTime().hour()) > eventData){
            this->_actuator->switchOn();
        }
    }
    else{
        if(config->getMinValue(QTime::currentTime().hour()) < eventData){
            this->_actuator->switchOn();
        }

        else if(config->getMaxValue(QTime::currentTime().hour()) > eventData){
            this->_actuator->switchOff();
        }
    }

}

QString ActuatorManager::getConfig(QString uuid)
{
    Sensor *sensor = this->sensorIds[QUuid(uuid)];
    if(sensor) {
        SensorConfig * config = this->configurations[sensor];
        if(config) {
            return config->toString();
        }
    }

    return "";
}


