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

signals:

public slots:

private:
   ActuatorList& actuators;
   QSharedPointer<RCSwitch> rcSwitch;
};

#endif // ACTORFACTORY_H
