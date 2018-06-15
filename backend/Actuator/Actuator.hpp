#ifndef ACTUATOR_H
#define ACTUATOR_H


#include "./../Sensor.h"
#include "./../RCSwitch/RCSwitch.h"
#include <string>

class Actuator{
    
    public:
    Actuator(std::string, int, RCSwitch*);

    void switchOn();
    void switchOff();
    int getId();
    bool isOn();


    private:
        
        bool _isActive;
        int _id;
        std::string _commandOn;
        std::string _commandOff;
        RCSwitch* _switch;
        

};

#endif