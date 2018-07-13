#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "./backend/Sensors/Sensor.h"
#include "sensorlist.h"

class Actuator;
class ActuatorManager : public QObject
{
    Q_OBJECT
public:
    explicit ActuatorManager(QObject *parent = nullptr);
    void registerActuator(Actuator& actuator);
    bool registerSensor(Sensor* , sensor_config*);
    Q_INVOKABLE SensorList& getSensors();

signals:

public slots:
    void eventReceived(sensors_event_t*);

private:
    SensorList sensorList;
    QMap<Sensor*, sensor_config*> configurations;
    QMap<QUuid, Sensor*> sensorIds;

    Actuator* _actuator;
};

#endif // CONFIGMANAGER_H
