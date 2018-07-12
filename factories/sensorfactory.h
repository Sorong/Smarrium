#ifndef SENSORFACTORY_H
#define SENSORFACTORY_H

#include <QObject>
#include "./../logic/channel.h"
#include "./../logic/gpio.h"
#include "./../backend/Sensors/Sensor.h"
#include "./../backend/Sensors/ADC.hpp"
#include "./../backend/Sensors/Bcm2835Interface.hpp"

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

    Bcm2835Interface* interface;
    ADC* adc;
};

#endif // SENSORFACTORY_H
