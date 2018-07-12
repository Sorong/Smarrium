#ifndef SENSORFACTORY_H
#define SENSORFACTORY_H

#include <QObject>
#include <QSharedPointer>
#include "logic/gpiomanager.h"
#include "logic/gpiolist.h"
#include "./../logic/channel.h"
#include "./../logic/gpio.h"
#include "./../backend/Sensors/Sensor.h"
#include "./../backend/Sensors/ADC.hpp"
#include "./../backend/Sensors/Bcm2835Interface.hpp"
class SensorFactory : public QObject
{
    Q_OBJECT
public:
    explicit SensorFactory(GPIOList& available, QObject *parent = nullptr);

    void addAnalogSensor(int interval, CHANNEL channel, sensors_type_t sensor);
    void addDigitalSensor(int interval, GPIO gpio, sensors_type_t sensor);
    void addI2CSensor(int interval, sensors_type_t sensor);
    void addAnalogSensor(CHANNEL channel, sensors_type_t sensor);
    void addDigitalSensor(GPIO gpio, sensors_type_t sensor);
    void addI2CSensor(sensors_type_t sensor);
signals:

public slots:

private:
    GPIOList &available;
    QSharedPointer<Bcm2835Interface> interface;
    QSharedPointer<ADC> adc;
    const int DEFAULT_INTERVAL_MS = 300000;
};

#endif // SENSORFACTORY_H
