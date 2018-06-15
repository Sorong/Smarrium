#include "configmanager.h"

ConfigManager::ConfigManager(QSharedPointer<Actuator> acturator, QObject *parent) : QObject(parent)
{
    this->_actuator = acturator;
}

bool ConfigManager::registerSensor(QSharedPointer<Sensor> sensor, sensor_config* config)
{
    this->_sensorList.push_back(sensor);
    this->_configList.push_back(config);
    connect(sensor.data(), SIGNAL(newSensorEvent(sensors_event_t*)), this, SLOT(eventRecived(sensors_event_t*)));
    return true;
}

void ConfigManager::eventRecived(sensors_event_t* event)
{
    sensor_config* config;
    for(int index = 0; index <= this->_configList.count(); index++){
        if(this->_configList[index]->sensorId == event->sensor_id){
            config = this->_configList[index];
            break;
        }
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

    }
    if(config->minValue < eventData){
        this->_actuator->switchOn();
    }

    else if(config->maxValue > eventData){
        this->_actuator->switchOff();
    }

    delete event;
}


