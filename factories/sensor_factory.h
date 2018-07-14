#ifndef SENSORFACTORY_H
#define SENSORFACTORY_H

#include <QObject>
#include <QSet>
#include <QSharedPointer>
#include <logic/channelmap.h>
#include <logic/gpiomap.h>
#include "logic/sensorlist.h"
#include "logic/sensorstringlist.h"
#include "logic/gpiolist.h"
#include "logic/channel.h"
#include "logic/gpio.h"
#include "backend/Sensors/Sensor.h"
#include "backend/Sensors/ADC.hpp"
#include "backend/Sensors/Bcm2835Interface.hpp"
#include "backend/Sensors/AnalogSensor/MoistureSensor/MoistureSensor.hpp"
#include "backend/Sensors/AnalogSensor/UVSensor/UVSensor.hpp"
#include "backend/Sensors/DigitalSensor/HumiditySensor/HumiditySensor.hpp"
#include "backend/Sensors/DigitalSensor/TemperatureSensor/TemperatureSensor.hpp"
#include "backend/Sensors/I2CSensor/InfraredTemperatureSensor/InfraredTemperatureSensor.hpp"
#include "backend/Sensors/I2CSensor/LightSensor/LightSensor.hpp"

class SensorFactory : public QObject
{
    Q_OBJECT
public:
    explicit SensorFactory(GPIOList& available, SensorList& sensors, QObject *parent = nullptr);

    void addAnalogSensor(int interval, CHANNEL channel, sensors_type_t sensor);
    void addDigitalSensor(int interval, GPIO gpio, sensors_type_t sensor);
    void addI2CSensor(int interval, sensors_type_t sensor);
    Q_INVOKABLE void addAnalogSensor(QString channel, QString sensor);
    void addAnalogSensor(CHANNEL channel, sensors_type_t sensor);
    Q_INVOKABLE void addDigitalSensor(QString gpio, QString sensor);
    void addDigitalSensor(GPIO gpio, sensors_type_t sensor);
    Q_INVOKABLE void addI2CSensor(QString sensor);
    void addI2CSensor(sensors_type_t sensor);
    void getSensorTypes(SensorStringList *list);
    Q_INVOKABLE bool isAnalog(QString str);
    Q_INVOKABLE bool isDigital(QString str);
    Q_INVOKABLE bool isI2C(QString str);
signals:

public slots:

private:
    GPIOList &available;
    SensorList& sensors;
    SensorMap sensorMap;
    GPIOMap gpioMap;
    ChannelMap channelMap;
    QSet<sensor_type_t> analogSenors;
    QSet<sensor_type_t> digitalSensors;
    QSet<sensor_type_t> i2cSensors;
    QSharedPointer<Bcm2835Interface> interface;
    QSharedPointer<ADC> adc;
    const int DEFAULT_INTERVAL_MS = 300000;
    uint32_t irDefaultAdress = 0x5A;
    uint8_t numberLightSensors = 0;
    uint8_t lightAdress[3] = {0x29, 0x39, 0x49};
};

#endif // SENSORFACTORY_H
