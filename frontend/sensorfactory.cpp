#include "sensorfactory.h"

SensorFactory::SensorFactory(QObject *parent) : QObject(parent)
{
    this->adc = new ADC();
    this->interface = new Bcm2835Interface();
}

void SensorFactory::addAnalogSensor(int interval, CHANNEL channel, sensors_type_t sensorType){
    switch(sensorType){

    case SENSOR_TYPE_MOISTURE:
        break;

    case SENSOR_TYPE_UV:
        break;
    }
}

void SensorFactory::addDigitalSensor(int interval, GPIO gpio, sensors_type_t sensorType){

}

void SensorFactory::addI2CSensor(int interval, sensors_type_t sensorType){

}
