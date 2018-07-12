#include "actorfactory.h"

ActorFactory::ActorFactory(QObject *parent) : QObject(parent)
{
    this->rcSwitch = new RCSwitch();
    this->rcSwitch->enableTransmit(0);
}

void ActorFactory::addActuator(bool flipSwitch[]){
    std::string socketCombination("");
    for(int index = 0; index < 10; index++){
        if(flipSwitch[index] == true){
            socketCombination.append("0");
        }
        else{
            socketCombination.append("F");
        }
    }
    Actuator actuator(socketCombination, this->rcSwitch);
}
