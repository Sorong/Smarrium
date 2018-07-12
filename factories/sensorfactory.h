#ifndef SENSORFACTORY_H
#define SENSORFACTORY_H

#include <QObject>
#include <QSharedPointer>


#include "./../logic/channel.h"
#include "./../logic/gpio.h"
#include "./../backend/Sensors/Sensor.h"
#include "./../backend/Sensors/ADC.hpp"
#include "./../backend/Sensors/Bcm2835Interface.hpp"
#include "./../backend/Sensors/AnalogSensor/MoistureSensor/MoistureSensor.hpp"
#include "./../backend/Sensors/AnalogSensor/UVSensor/UVSensor.hpp"
#include "./../backend/Sensors/DigitalSensor/HumiditySensor/HumiditySensor.hpp"
#include "./../backend/Sensors/DigitalSensor/TemperatureSensor/TemperatureSensor.hpp"
#include "./../backend/Sensors/I2CSensor/InfraredTemperatureSensor/InfraredTemperatureSensor.hpp"
#include "./../backend/Sensors/I2CSensor/LightSensor/LightSensor.hpp"

class SensorFactory : public QObject
{
    Q_OBJECT
public:
    explicit SensorFactory(QObject *parent = nullptr);

    void addAnalogSensor(int interval, CHANNEL channel, sensors_type_t);
    void addDigitalSensor(int interval, GPIO gpio, sensors_type_t);
    void addI2CSensor(int interval, sensors_type_t sensor);

signals:

public slots:

private:

    uint32_t irDefaultAdress = 0x5A;
    uint8_t numberLightSensors = 0;
    uint8_t lightAdress[3] = {0x29, 0x39, 0x49};
    Bcm2835Interface* interface;
    ADC* adc;
};

#endif // SENSORFACTORY_H
