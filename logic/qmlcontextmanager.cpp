#include <QQmlContext>
#include "qmlcontextmanager.h"

QMLContextManager::QMLContextManager(QQmlApplicationEngine& engine, QObject *parent) : QObject(parent), engine(engine)
{
    this->actuatorFactory = QSharedPointer<ActuatorFactory>(new ActuatorFactory(this->existingActuators));
    this->sensorFactory = QSharedPointer<SensorFactory>(new SensorFactory(this->gpioAvailable, this->existingSensors));
    this->sensorFactory->getSensorTypes(&this->supportedSensors);
    this->gpioManager.getAvailable(&this->gpioAvailable);
    this->gpioManager.getUnavailable(&this->gpioUnavailable);
    this->channelManager.getAvailable(&this->channelAvailable);
    this->channelManager.getUnavailable(&this->channelUnavailable);
}

void QMLContextManager::init()
{
    QQmlContext *context = this->engine.rootContext();
    context->setContextProperty("gpioAvailable", &gpioAvailable);
    context->setContextProperty("gpioUnavailable", &gpioUnavailable);
    context->setContextProperty("actuators", &existingActuators);
    context->setContextProperty("sensors", &existingSensors);
    context->setContextProperty("actuatorFactory", actuatorFactory.data());
    context->setContextProperty("sensorFactory", sensorFactory.data());
    context->setContextProperty("supportedSensors", &supportedSensors);
    context->setContextProperty("channelAvailable", &channelAvailable);
    connect(&this->existingActuators, &ActuatorList::onSelect, this, &QMLContextManager::selectActuator);
    //connect(sender, SIGNAL(destroyed()), this, SLOT(objectDestroyed()));
}

void QMLContextManager::selectActuator(Actuator *actuator)
{
    if(!actuator) {
        return;
    }
    if(this->selectedSensors) {
        this->existingSensors.disconnect(this->selectedSensors);
    }
    QQmlContext * context = this->engine.rootContext();
    this->selectedSensors = &(actuator->getManager().getSensors());
    context->setContextProperty("selectedSensors", this->selectedSensors);
    connect(&this->existingSensors, &SensorList::onSelect, this->selectedSensors, &SensorList::addUnique);
}
