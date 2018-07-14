#include "./Actuator.hpp"

Actuator::Actuator(QString baseAdress, RCSwitch* rcSwitch){
    this->_commandOff = baseAdress.toStdString();
    this->_commandOn = baseAdress.toStdString();
    this->_code = baseAdress;
    this->_commandOn.append(ON_SUFFIX);
    this->_commandOff.append(OFF_SUFFIX);
    this->_switch = rcSwitch;
    this->switchOff();
    this->manager.registerActuator(*this);
}

Actuator::~Actuator()
{

}


void Actuator::switchOff(){
    this->_switch->sendTriState(this->_commandOff.c_str());
    this->_isActive = false;
}

void Actuator::switchOn(){
    this->_switch->sendTriState(this->_commandOn.c_str());
    this->_isActive = true;
}

QString& Actuator::getCode(){
    return this->_code;
}

ActuatorManager &Actuator::getManager()
{
    return this->manager;
}
