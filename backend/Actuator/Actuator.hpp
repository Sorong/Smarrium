#ifndef ACTUATOR_H
#define ACTUATOR_H

#define OFF_SUFFIX "F0"
#define ON_SUFFIX "0F"

#include "./../Sensors/Sensor.h"
#include "./../RCSwitch/RCSwitch.h"
#include <string>
#include <stdio.h>

class Actuator{
    
    public:
    Actuator(std::string, RCSwitch*);

    void switchOn();
    void switchOff();
    std::string getCode();
    bool isOn();


    private:
        
        bool _isActive;
        std::string _code;
        std::string _commandOn;
        std::string _commandOff;
        RCSwitch* _switch;
        

};

#endif
