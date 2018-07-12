#include "sensor_factory.h"

SensorFactory::SensorFactory(GPIOList& available, QObject *parent) : QObject(parent), available(available)
{
    this->adc = QSharedPointer<ADC>(new ADC());
    this->interface = QSharedPointer<Bcm2835Interface>(new Bcm2835Interface());
}

void SensorFactory::addAnalogSensor(int interval, CHANNEL channel, sensors_type_t sensorType){
    switch(sensorType){

    case SENSOR_TYPE_MOISTURE:
        break;

    case SENSOR_TYPE_UV:
        break;
    default:
            break;
    }
}

void SensorFactory::addDigitalSensor(int interval, GPIO gpio, sensors_type_t sensorType){

}

void SensorFactory::addI2CSensor(int interval, sensors_type_t sensorType){

}

void SensorFactory::addAnalogSensor(CHANNEL channel, sensors_type_t sensor)
{
    this->addAnalogSensor(DEFAULT_INTERVAL_MS, channel, sensor);
}

void SensorFactory::addDigitalSensor(GPIO gpio, sensors_type_t sensor)
{
    this->addDigitalSensor(DEFAULT_INTERVAL_MS, gpio, sensor);
}

void SensorFactory::addI2CSensor(sensors_type_t sensor)
{
    this->addI2CSensor(DEFAULT_INTERVAL_MS, sensor);
}
