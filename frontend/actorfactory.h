#ifndef ACTORFACTORY_H
#define ACTORFACTORY_H

#include <QObject>
#include <string.h>
#include "./../backend/Actuator/Actuator.hpp"
#include "./../backend/RCSwitch/RCSwitch.h"

class ActorFactory : public QObject
{
    Q_OBJECT
public:
    explicit ActorFactory(QObject *parent = nullptr);
    void addActor(bool flipSwitch[]);

signals:

public slots:

private:
   RCSwitch* rcSwitch;
};

#endif // ACTORFACTORY_H
