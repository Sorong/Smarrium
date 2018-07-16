#ifndef CONFIGFACTORY_H
#define CONFIGFACTORY_H

#include <QObject>
#include "backend/Sensors/sensorbasetype.h"

class ConfigFactory : public QObject
{
    Q_OBJECT
public:
    explicit ConfigFactory(QObject *parent = nullptr);

signals:

public slots:
    Q_INVOKABLE QString getConfig(SensorBaseType type);
private:
    QString readFromFile(SensorBaseType type);
};

#endif // CONFIGFACTORY_H
