#include "./Actuator.hpp"

Actuator::Actuator(std::string baseAdress, int id, RCSwitch* rcSwitch){
    this->_commandOff = baseAdress;
    this->_commandOn = baseAdress;
    this->_code = baseAdress;
    this->_commandOn.append(ON_SUFFIX);
    this->_commandOff.append(OFF_SUFFIX);
    this->_id = id;
    this->_switch = rcSwitch;
    this->switchOff();
}

void Actuator::switchOff(){
    this->_switch->sendTriState(this->_commandOff.c_str());
    this->_isActive = false;
}

void Actuator::switchOn(){
    this->_switch->sendTriState(this->_commandOn.c_str());
    this->_isActive = true;
}

std::string Actuator::getCode(){
    return this->_code;
}
