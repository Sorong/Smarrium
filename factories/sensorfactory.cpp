#include "sensorfactory.h"

SensorFactory::SensorFactory(QObject *parent) : QObject(parent)
{
    this->adc = new ADC();
    this->interface = new Bcm2835Interface();
}

void SensorFactory::addAnalogSensor(int interval, CHANNEL channel, sensors_type_t sensorType){

    switch(sensorType){

    case SENSOR_TYPE_MOISTURE:
    {
        QSharedPointer<MoistureSensor> moistureSensor = QSharedPointer<MoistureSensor>(new MoistureSensor(interval, channel, this->adc));
        break;
    }
    case SENSOR_TYPE_UV:
    {
        //todo: Change to one channel
        QSharedPointer<UVSensor> uvSensor = QSharedPointer<UVSensor>(new UVSensor(interval, channel, channel, this->adc));
        break;
    }
    default:
        return;
    }
}

void SensorFactory::addDigitalSensor(int interval, GPIO gpio, sensors_type_t sensorType){
    switch(sensorType){

    case SENSOR_TYPE_RELATIVE_HUMIDITY:
    {
        QSharedPointer<HumiditySensor> humiditySensor = QSharedPointer<HumiditySensor>(new HumiditySensor(interval, gpio, this->interface));
        break;
    }
    case SENSOR_TYPE_TEMPERATURE:
    {
        QSharedPointer<TemperatureSensor> temperatureSensor = QSharedPointer<TemperatureSensor>(new TemperatureSensor(interval, gpio, this->interface));
        break;
    }
    default:
        return;
    }
}

void SensorFactory::addI2CSensor(int interval, sensors_type_t sensorType){
    uint8_t address;

    switch(sensorType){

    case SENSOR_TYPE_IRTEMPERATURE:
    {
        address = irDefaultAdress++;
        QSharedPointer<IRTemperatureSensor> irTemperatureSensor = QSharedPointer<IRTemperatureSensor>(new IRTemperatureSensor(interval, address, this->interface));
        break;
    }
    case SENSOR_TYPE_LIGHT:
    {
        address = lightAdress[numberLightSensors];
        QSharedPointer<LightSensor> irTemperatureSensor = QSharedPointer<LightSensor>(new LightSensor(interval, address, this->interface));
        numberLightSensors++;
        break;
    }
    default:
        return;
    }
}
