#include "sensor_factory.h"


SensorFactory::SensorFactory(GPIOList& available,SensorList& sensors, QObject *parent) : QObject(parent), available(available), sensors(sensors)
{
    this->adc = QSharedPointer<ADC>(new ADC());
    this->interface = QSharedPointer<Bcm2835Interface>(new Bcm2835Interface());
}

void SensorFactory::addAnalogSensor(int interval, CHANNEL channel, sensors_type_t sensorType){

    switch(sensorType){

    case SENSOR_TYPE_MOISTURE:
    {
        QSharedPointer<MoistureSensor> moistureSensor = QSharedPointer<MoistureSensor>(new MoistureSensor(interval, channel, this->adc.data()));
        break;
    }
    case SENSOR_TYPE_UV:
    {
        //todo: Change to one channel
        QSharedPointer<UVSensor> uvSensor = QSharedPointer<UVSensor>(new UVSensor(interval, channel, channel, this->adc.data()));
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
        QSharedPointer<HumiditySensor> humiditySensor = QSharedPointer<HumiditySensor>(new HumiditySensor(interval, gpio, this->interface.data()));
        break;
    }
    case SENSOR_TYPE_TEMPERATURE:
    {
        QSharedPointer<TemperatureSensor> temperatureSensor = QSharedPointer<TemperatureSensor>(new TemperatureSensor(interval, gpio, this->interface.data()));
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
        QSharedPointer<IRTemperatureSensor> irTemperatureSensor = QSharedPointer<IRTemperatureSensor>(new IRTemperatureSensor(interval, address, this->interface.data()));
        break;
    }
    case SENSOR_TYPE_LIGHT:
    {
        address = lightAdress[numberLightSensors];
        QSharedPointer<LightSensor> irTemperatureSensor = QSharedPointer<LightSensor>(new LightSensor(interval, address, this->interface.data()));
        numberLightSensors++;
        break;
    }
    default:
        return;
    }
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
