#ifndef QMLCONTEXTMANAGER_H
#define QMLCONTEXTMANAGER_H

#include <QObject>
#include <QQmlApplicationEngine>

#include "actuatorlist.h"
#include "channelmanager.h"
#include "gpiomanager.h"
#include "sensorlist.h"
#include "sensorstringlist.h"


#include <factories/actuator_factory.h>
#include <factories/sensor_factory.h>

class QMLContextManager : public QObject
{
    Q_OBJECT
public:
    explicit QMLContextManager(QQmlApplicationEngine& engine, QObject *parent = nullptr);
    void init();

signals:

public slots:
    void selectActuator(Actuator *actuator);

private:
    QQmlApplicationEngine& engine;
    GPIOManager gpioManager;
    GPIOList gpioAvailable;
    GPIOList gpioUnavailable; //Notwendig?
    ChannelManager channelManager;
    ChannelList channelAvailable;
    ChannelList channelUnavailable; //Notwendig?

    SensorStringList supportedSensors;

    SensorList existingSensors;
    ActuatorList existingActuators;

    QSharedPointer<ActuatorFactory> actuatorFactory;
    QSharedPointer<SensorFactory>  sensorFactory;
    //Actuator *selectedActuator; notwendig?
    ActuatorList *selectedActuators;
    SensorList *selectedSensors;
};

#endif // QMLCONTEXTMANAGER_H
