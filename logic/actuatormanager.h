#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include <backend/Sensors/sensorconfig.h>

#include "./backend/Sensors/Sensor.h"
#include "sensorlist.h"

class Actuator;
class ActuatorManager : public QObject
{
    Q_OBJECT
public:
    explicit ActuatorManager(QObject *parent = nullptr);
    void registerActuator(Actuator& actuator);
    bool registerSensor(Sensor& sensor, SensorConfig& config);

    Q_INVOKABLE SensorList& getSensors();

signals:

public slots:
    bool unregisterSensor(Sensor* sensor);
    void eventReceived(sensors_event_t*);
    QString getConfig(QString uuid);

private:
    SensorList sensorList;
    bool isBlocked(sensors_event_t&);
    QMap<Sensor*, SensorConfig*> configurations;
    QMap<QUuid, Sensor*> sensorIds;
    QMap<QUuid, SensorConfig*> runtimeConfigurations;

    Actuator* _actuator;
};

#endif // CONFIGMANAGER_H
