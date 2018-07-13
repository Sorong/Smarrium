#include "actuatormanager.h"
#include "backend/Actuator/Actuator.hpp"

ActuatorManager::ActuatorManager(QObject *parent) : QObject(parent)
{
}

void ActuatorManager::registerActuator(Actuator &actuator)
{
    this->_actuator = &actuator;
}

bool ActuatorManager::registerSensor(Sensor* sensor, sensor_config* config)
{
    this->sensorList.add(sensor);
    this->configurations[sensor] = config;
    this->sensorIds[sensor->getId()] = sensor;
    connect(sensor, SIGNAL(newSensorEvent(sensors_event_t*)), this, SLOT(eventRecived(sensors_event_t*)));
    return true;
}

SensorList &ActuatorManager::getSensors()
{
    return this->sensorList;
}

void ActuatorManager::eventReceived(sensors_event_t* event)
{
    if(!_actuator) {
        return;
    }
    sensor_config* config = this->configurations[sensorIds[event->sensor_id]];
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

    }
    if(config->minValue < eventData){
        this->_actuator->switchOn();
    }

    else if(config->maxValue > eventData){
        this->_actuator->switchOff();
    }

    //delete event;
}


