#include "actuatormanager.h"
#include "backend/Actuator/Actuator.hpp"
#include <QDebug>
#include <QJsonDocument>
#include "backend/Sensors/sensorbasetype.h"

ActuatorManager::ActuatorManager(QObject *parent) : QObject(parent)
{
    connect(&(this->sensorList), &SensorList::onRemove, this, &ActuatorManager::unregisterSensor);
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
    this->configurations.insert(&sensor, &config);
    this->setLimit(config.getLimit());
    this->setCooldown(config.getCooldown());

    if(!this->sensorIds.contains(sensor.getId())) {
        connect(&sensor, SIGNAL(newSensorEvent(sensors_event_t*)), this, SLOT(eventReceived(sensors_event_t*)));
        this->sensorIds[sensor.getId()] = &sensor;
    }



    if(sensor.getRawType() == SensorBaseType::CLOCK) {
        this->runtimeConfigurations.insert(sensor.getId(), &config);
    }
    return true;
}

bool ActuatorManager::unregisterSensor(Sensor *sensor)
{
    if(!sensor) {
        return false;
    }
    this->configurations.remove(sensor);
    this->sensorIds.remove(sensor->getUuid());
    this->runtimeConfigurations.remove(sensor->getUuid());
    return true;
}

SensorList &ActuatorManager::getSensors()
{
    return this->sensorList;
}

void ActuatorManager::setLimit(int limit)
{
    if(limit == 0)
        return;

    if(this->limit == -1) {
        qDebug() << "Limit set to:" << limit;
        this->limit = limit;
    } else if (this->limit < limit) {
        qDebug() << "Limit set to:" << limit;
        this->limit = limit;
    }
}

void ActuatorManager::setCooldown(int cooldown)
{
    if(cooldown == 0)
        return;

    if(this->cooldown == -1) {
        qDebug() << "Cooldown set to:" << cooldown;
        this->cooldown = cooldown;
    } else if (this->cooldown < cooldown) {
        qDebug() << "Cooldown set to:" << cooldown;
        this->cooldown = cooldown;
    }
}

void ActuatorManager::eventReceived(sensors_event_t* event)
{
    //qDebug() << "Event recived: " << event->timestamp;
    if(!_actuator || !event) {
        return;
    }

    SensorConfig* config = this->configurations[sensorIds[event->sensor_id]];
    if(!config) {
        return;
    }

    if(limit != -1) {
        int lastStart = this->activatedAt.elapsed();
        if(this->_actuator->isOn() && lastStart >= limit) {
            qDebug() << "Limit reached " << lastStart;
            this->switchOff();
            this->_actuator->switchOff();
            return;
        } else if (lastStart != 0 && !this->_actuator->isOn() && lastStart <= (limit+cooldown)) {
            qDebug() << "remaining cooldown " << ((limit + cooldown) - lastStart);
            this->_actuator->switchOff();
            return;
        }
    }

    if(this->isBlocked(*event)) {
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
    default:
        break;
    }

    if(config->ignoreSwitches()){
        return;
    }

    if(event->type == SENSOR_TYPE_CLOCK) {
        this->processClockEvent(*config);
    } else {
        this->processEventData(eventData, *config);
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

void ActuatorManager::processEventData(float eventData, SensorConfig &config)
{

    if (config.minIsOff()){
        if(config.getMinValue(QTime::currentTime().hour()) > eventData){
            this->switchOff();
        }

        else if(config.getMaxValue(QTime::currentTime().hour()) < eventData){
            this->switchOn();
        }
    }
    else{
        if(config.getMinValue(QTime::currentTime().hour()) > eventData){
            this->switchOn();
        }

        else if(config.getMaxValue(QTime::currentTime().hour()) < eventData){
            this->switchOff();
        }
    }
}

void ActuatorManager::processClockEvent(SensorConfig &config)
{
    int hour = QTime::currentTime().hour();
    int start = config.getStart();
    int stop = config.getStop();
    if(config.ignoreOn() && !this->_actuator->isOn()) {
        //qDebug() << "ignore on";
        return;
    }
    if(config.ignoreOff() && this->_actuator->isOn()) {
        //qDebug() << "ignore off";
        return;
    }

    if((start == stop) || (hour >= start && hour <= stop)) {
        this->switchOn();
    } else if((stop < start) && !(hour >= stop  && hour <= start)) {
        this->switchOn();
    } else {
        this->_actuator->switchOff();
    }
}

void ActuatorManager::switchOn()
{
    if(!this->_actuator->isOn()) {
        qDebug() << "Switched on at " << QTime::currentTime();
        //for(int i = 0; i < 10; i++){
            this->_actuator->switchOn();
       // }
        this->_actuator->switchOn();
        this->activatedAt.start();
    }
}

void ActuatorManager::switchOff()
{
    if(this->_actuator->isOn()) {
        qDebug() << "Switched off at: " << QTime::currentTime();
        this->_actuator->switchOff();
    }
}

bool ActuatorManager::isBlocked(sensors_event_t &ev)
{

    Sensor* sensor = this->sensorIds[ev.sensor_id];
    if(!sensor) {
        return true;
    }
    if(sensor->getRawType() == SensorBaseType::CLOCK) {
        return false;
    }
    int hour = ev.timestamp.hour();
    for(auto key : this->runtimeConfigurations.keys()) {
        SensorConfig * config = this->runtimeConfigurations[key];
        if(config) {
            int start = config->getStart();
            int stop = config->getStop();
            if((start == stop) || (hour >= start && hour <= stop)) {
                return false;
            } else if((stop < start) && !(hour >= stop  && hour <= start)) {
                return false;
            }
        }

    }
    return true;
}





