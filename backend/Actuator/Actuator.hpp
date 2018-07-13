#ifndef ACTUATOR_H
#define ACTUATOR_H

#define OFF_SUFFIX "F0"
#define ON_SUFFIX "0F"
#include <QObject>
#include "./../Sensors/Sensor.h"
#include "./../RCSwitch/RCSwitch.h"
#include <string>
#include <stdio.h>
#include <logic/actuatormanager.h>

class Actuator : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString code READ getCode)
public:
    Actuator(QString, RCSwitch*);
    virtual ~Actuator();

    void switchOn();
    void switchOff();
    Q_INVOKABLE QString& getCode();
    bool isOn();

    Q_INVOKABLE const ActuatorManager& getManager();
private:
    ActuatorManager manager;
    bool _isActive;
    QString _code;
    std::string _commandOn;
    std::string _commandOff;
    RCSwitch* _switch;


};

#endif
