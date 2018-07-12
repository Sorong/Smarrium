#include <QDebug>
#include "actuator_factory.h"

ActuatorFactory::ActuatorFactory(ActuatorList& actuators, QObject *parent) :  QObject(parent), actuators(actuators)
{
    this->rcSwitch = QSharedPointer<RCSwitch>(new RCSwitch());
    this->rcSwitch->enableTransmit(0);
}

void ActuatorFactory::addActuator(QList<bool> flipSwitch){
    qDebug() << "addActuator";
    std::string socketCombination("");
    for(int index = 0; index < flipSwitch.size(); index++){
        socketCombination.append(flipSwitch[index] ? "0" : "F");
    }
    QSharedPointer<Actuator> actuator = QSharedPointer<Actuator>(new Actuator(socketCombination, this->rcSwitch.data()));
    this->actuators.addActuator(actuator);
}
