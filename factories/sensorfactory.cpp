#include "sensorfactory.h"

SensorFactory::SensorFactory(QObject *parent) : QObject(parent)
{
    this->adc = new ADC();
    this->interface = new Bcm2835Interface();
}

void SensorFactory::addAnalogSensor(int interval, CHANNEL channel, sensors_type_t sensorType){
    switch(sensorType){

    case SENSOR_TYPE_MOISTURE:
        MoistureSensor moistureSensor(interval, channel, this->adc);
        break;

    case SENSOR_TYPE_UV:
        UVSensor uvSensor(interval, channel, channel, this->adc);
        break;

    default:
        return;
    }
}

void SensorFactory::addDigitalSensor(int interval, GPIO gpio, sensors_type_t sensorType){
    switch(sensorType){

    case SENSOR_TYPE_RELATIVE_HUMIDITY:
        HumiditySensor humiditySensor(interval, gpio, this->interface);
        break;

    case SENSOR_TYPE_TEMPERATURE:
        TemperatureSensor temperatureSensor(interval, gpio, this->interface);
        break;

    default:
        return;
    }
}

void SensorFactory::addI2CSensor(int interval, sensors_type_t sensorType){
    uint8_t adress;

    switch(sensorType){
    case SENSOR_TYPE_IRTEMPERATURE:
        adress = irDefaultAdress++;
        IRTemperatureSensor irTemperatureSensor(interval, adress, this->interface);
        break;

    case SENSOR_TYPE_LIGHT:
        adress = lightAdress[numberLightSensors];
        LightSensor lightSensor(interval, adress, this->interface);
        numberLightSensors++;
        break;

    default:
        return;
    }
}
