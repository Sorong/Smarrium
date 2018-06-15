#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QList>
#include <QSharedPointer>
#include "./backend/Actuator/Actuator.hpp"
#include "./backend/Sensors/Sensor.h"

class ConfigManager : public QObject
{
    Q_OBJECT
public:
    explicit ConfigManager(QSharedPointer<Actuator>, QObject *parent = nullptr);
    bool registerSensor(QSharedPointer<Sensor>, sensor_config*);

signals:

public slots:
    void eventRecived(sensors_event_t*);

private:
    QList<QSharedPointer<Sensor>> _sensorList;
    QList<sensor_config*> _configList;
    QSharedPointer<Actuator> _actuator;
};

#endif // CONFIGMANAGER_H
