#include "Actuator.hpp"

Actuator::Actuator(QString baseAdress, int id, QSharedPointer<RCSwitch> rcSwitch){
    this->_commandOn = baseAdress.append("0F");
    this->_commandOff = baseAdress.append("F0");
    this->_id = id;
    this->_switch = rcSwitch;
    this->switchOff();
}

void Actuator::switchOff(){
    // this->_switch->sendTriState(this->_commandOff.c_str());
    // this->_isActive = false;
    //this->_switch->send(5592401,24);
}


void Actuator::switchOn(){
    // this->_switch->sendTriState(this->_commandOn.c_str());
    // this->_isActive = true;
    //this->_switch->send(5592406,24);
}

int Actuator::getId(){
    return this->_id;
}
