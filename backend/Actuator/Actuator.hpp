#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <QSharedPointer>
#include "backend/Sensors/Sensor.h"
#include "backend/RCSwitch/RCSwitch.h"
#include <string>


class Actuator{
    
    public:
    Actuator(QString, int, QSharedPointer<RCSwitch>);

    void switchOn();
    void switchOff();
    int getId();
    bool isOn();


    private:
        
        bool _isActive;
        int _id;
        QString _commandOn;
        QString _commandOff;
        QSharedPointer<RCSwitch> _switch;
        

};

#endif
