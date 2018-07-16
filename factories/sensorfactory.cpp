#include <QDebug>
#include <backend/Sensors/VirtualSensor/Camera/camera.h>
#include <backend/Sensors/VirtualSensor/Clock/clocksensor.h>
#include "sensorfactory.h"


SensorFactory::SensorFactory(GPIOList& available, SensorList& sensors, QObject *parent) : QObject(parent), available(available), sensors(sensors)
{
    this->adc = QSharedPointer<ADC>(new ADC());
    this->interface = QSharedPointer<Bcm2835Interface>(new Bcm2835Interface());
    this->analogSenors = {SENSOR_TYPE_MOISTURE, SENSOR_TYPE_UV};
    this->digitalSensors = {SENSOR_TYPE_RELATIVE_HUMIDITY, SENSOR_TYPE_TEMPERATURE};
    this->i2cSensors = {SENSOR_TYPE_IRTEMPERATURE, SENSOR_TYPE_LIGHT, SENSOR_TYPE_CAMERA};
}

void SensorFactory::addAnalogSensor(int interval, CHANNEL channel, sensors_type_t sensorType){
    qDebug() << "addAnalogSensor";
    Sensor *ptr = nullptr;
    switch(sensorType){

    case SENSOR_TYPE_MOISTURE:
    {
        ptr = new MoistureSensor(interval, channel, this->adc.data());
        break;
    }
    case SENSOR_TYPE_UV:
    {
        ptr = new UVSensor(interval, channel, this->adc.data());
        break;
    }
    default:
        return;
    }
    this->addToSensorList(ptr);
}

void SensorFactory::addDigitalSensor(int interval, GPIO gpio, sensors_type_t sensorType){
    qDebug() << "addDigitalSensor";
    Sensor *ptr = nullptr;
    switch(sensorType){

    case SENSOR_TYPE_RELATIVE_HUMIDITY:
    {
        ptr = new HumiditySensor(interval, gpio, this->interface.data());
        break;
    }
    case SENSOR_TYPE_TEMPERATURE:
    {
        ptr = new TemperatureSensor(interval, gpio, this->interface.data());
        break;
    }
    default:
        return;
    }
    this->addToSensorList(ptr);
}

void SensorFactory::addI2CSensor(int interval, sensors_type_t sensorType){
    qDebug() << "addI2CSensor";
    uint8_t address;
    Sensor *ptr = nullptr;

    switch(sensorType){
    case SENSOR_TYPE_IRTEMPERATURE:
    {
        address = irDefaultAdress++;
        ptr = new IRTemperatureSensor(interval, address, this->interface.data());
        break;
    }
    case SENSOR_TYPE_LIGHT:
    {
        address = lightAdress[numberLightSensors];
        ptr = new LightSensor(interval, address, this->interface.data());
        numberLightSensors++;
        break;
    }
    case SENSOR_TYPE_CAMERA:
        ptr = new Camera();
        break;
    case SENSOR_TYPE_CLOCK:
        ptr = new ClockSensor();
        break;
    default:
        return;
    }
    this->addToSensorList(ptr);
}

void SensorFactory::addAnalogSensor(QString channel, QString sensor)
{
    sensor_type_t type = this->sensorMap[sensor];
    CHANNEL chan = this->channelMap[channel];
    this->addAnalogSensor(chan, type);
}

void SensorFactory::addAnalogSensor(CHANNEL channel, sensors_type_t sensor)
{
    this->addAnalogSensor(DEFAULT_INTERVAL_MS, channel, sensor);
}

void SensorFactory::addDigitalSensor(QString gpio, QString sensor)
{
    sensor_type_t type = this->sensorMap[sensor];
    GPIO pin = this->gpioMap[gpio];
    this->addDigitalSensor(pin, type);
}

void SensorFactory::addDigitalSensor(GPIO gpio, sensors_type_t sensor)
{
    this->addDigitalSensor(DEFAULT_INTERVAL_MS, gpio, sensor);
}

void SensorFactory::addI2CSensor(QString sensor)
{
    sensor_type_t type = this->sensorMap[sensor];
    this->addI2CSensor(type);
}

void SensorFactory::addI2CSensor(sensors_type_t sensor)
{
    this->addI2CSensor(DEFAULT_INTERVAL_MS, sensor);
}

void SensorFactory::getSensorTypes(SensorStringList *list)
{
    if(list)
        list->setSensorStringList(this->sensorMap.getTypes());
}

bool SensorFactory::isAnalog(QString str)
{
    return this->analogSenors.contains(this->sensorMap[str]);
}

bool SensorFactory::isDigital(QString str)
{
    return this->digitalSensors.contains(this->sensorMap[str]);
}

bool SensorFactory::isI2C(QString str)
{
    return this->i2cSensors.contains(this->sensorMap[str]);
}

void SensorFactory::killEvent()
{
    sensors_event_t *sensor = this->occuredEvents.dequeue();
    if(sensor) {
        qDebug() << ";_;7 Rip sensors_event_t" <<  QDateTime::currentDateTime();
        delete sensor;
    }
}

void SensorFactory::eventCollector(sensors_event_t *ev)
{
    this->occuredEvents.enqueue(ev);
    QTimer::singleShot(2 * 60 * 1000, this, SLOT(killEvent())); //Garbagecollection after 2 minutes
}

void SensorFactory::addToSensorList(Sensor *sensor)
{
    if(sensor){
        this->sensors.add(sensor);
        connect(sensor, &Sensor::newSensorEvent, this, &SensorFactory::eventCollector);
    }
}
