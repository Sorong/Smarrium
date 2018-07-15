#ifndef ACTUATORFACTORY_H
#define ACTUATORFACTORY_H

#include <QObject>
#include <QSharedPointer>
#include <string.h>
#include "./../backend/Actuator/Actuator.hpp"
#include "./../backend/RCSwitch/RCSwitch.h"
#include "logic/actuatorlist.h"

class ActuatorFactory : public QObject
{
    Q_OBJECT
public:
    explicit ActuatorFactory(ActuatorList&, QObject *parent = nullptr);
    Q_INVOKABLE void addActuator(QList<bool> flipSwitch);
    void createActuatorConfig(Actuator& actuator, Sensor& sensor, SensorConfig& config);
signals:
    void onCreateActuatorConfig(QString uuid, QString config);

public slots:
    //bool ActuatorManager::registerSensor(Sensor* sensor, sensor_config* config)

    Q_INVOKABLE void createActuatorConfig(QString uuid, QString config);

private:
   ActuatorList& actuators;
   QSharedPointer<RCSwitch> rcSwitch;
};

#endif // ACTORFACTORY_H
