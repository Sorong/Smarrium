#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <QSharedPointer>
#include "backend/Sensors/Sensor.h"
#include "./../RCSwitch/RCSwitch.h"
#include <string>


class Actuator{
    
    public:
    Actuator(std::string, int, QSharedPointer<RCSwitch>);

    void switchOn();
    void switchOff();
    int getId();
    bool isOn();


    private:
        
        bool _isActive;
        int _id;
        std::string _commandOn;
        std::string _commandOff;
        QSharedPointer<RCSwitch> _switch;
        

};

#endif
