#include <QDebug>
#include <backend/Sensors/sensorconfig.h>
#include "actuatorfactory.h"

ActuatorFactory::ActuatorFactory(ActuatorList& actuators, QObject *parent) :  QObject(parent), actuators(actuators)
{
    this->rcSwitch = QSharedPointer<RCSwitch>(new RCSwitch());
    this->rcSwitch->enableTransmit(0);
}

void ActuatorFactory::addActuator(QList<bool> flipSwitch){
    qDebug() << "addActuator";
    QString socketCombination("");
    for(int index = 0; index < flipSwitch.size(); index++){
        socketCombination.append(flipSwitch[index] ? "0" : "F");
    }
    if(this->actuators.hasActuator(socketCombination)){
        return;
    };
    QSharedPointer<Actuator> actuator = QSharedPointer<Actuator>(new Actuator(socketCombination, this->rcSwitch.data()));
    this->actuators.addActuator(actuator);
}

void ActuatorFactory::createActuatorConfig(Actuator &actuator, Sensor &sensor, SensorConfig& config)
{
    ActuatorManager &manager = actuator.getManager();
    manager.registerSensor(sensor, config);
}

void ActuatorFactory::createActuatorConfig(QString uuid, QString config)
{
    emit onCreateActuatorConfig(uuid, config);
}


//TODO: Remove
