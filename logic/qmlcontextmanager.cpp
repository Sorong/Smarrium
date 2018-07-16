#include <QJsonDocument>
#include <QQmlContext>
#include "qmlcontextmanager.h"

QMLContextManager::QMLContextManager(QQmlApplicationEngine& engine, QObject *parent) : QObject(parent), engine(engine)
{
    this->actuatorFactory = QSharedPointer<ActuatorFactory>(new ActuatorFactory(this->existingActuators));
    this->sensorFactory = QSharedPointer<SensorFactory>(new SensorFactory(this->gpioAvailable, this->existingSensors));
    this->configFactory = QSharedPointer<ConfigFactory>(new ConfigFactory());
    this->sensorFactory->getSensorTypes(&this->supportedSensors);
    this->gpioManager.getAvailable(&this->gpioAvailable);
    this->gpioManager.getUnavailable(&this->gpioUnavailable);
    this->channelManager.getAvailable(&this->channelAvailable);
    this->channelManager.getUnavailable(&this->channelUnavailable);
    this->selectedActuator = nullptr;
    this->selectedActuatorManager = nullptr;
    //this->selectedActuators = nullptr;
    this->selectedSensors = nullptr;
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
    context->setContextProperty("configFactory", configFactory.data());
    context->setContextProperty("supportedSensors", &supportedSensors);
    context->setContextProperty("channelAvailable", &channelAvailable);
    context->setContextProperty("actuatorManager", this->selectedActuatorManager);
    connect(&this->existingActuators, &ActuatorList::onSelect, this, &QMLContextManager::selectActuator);
    connect(this->actuatorFactory.data(), &ActuatorFactory::onCreateActuatorConfig, this, &QMLContextManager::createConfig);
    //connect(sender, SIGNAL(destroyed()), this, SLOT(objectDestroyed()));
}

void QMLContextManager::selectActuator(Actuator *actuator)
{
    if(!actuator) {
        return;
    }
    this->selectedActuator = actuator;
    this->selectedActuatorManager = &actuator->getManager();
    if(this->selectedSensors) {
        this->existingSensors.disconnect(this->selectedSensors);
        this->disconnect(this->selectedSensors);
    }
    QQmlContext * context = this->engine.rootContext();
    this->selectedSensors = &(actuator->getManager().getSensors());
    context->setContextProperty("selectedSensors", this->selectedSensors);
    connect(&this->existingSensors, &SensorList::onSelect, this->selectedSensors, &SensorList::addUnique);
    connect(this->selectedSensors, &SensorList::onChangeConfig, this, &QMLContextManager::createConfig);
}

void QMLContextManager::createConfig(QString uuid, QString config)
{
    Actuator *actuator = this->selectedActuator;
    if(!actuator) {
        return;
    }
    Sensor *sensor;

    QUuid quuid(uuid);
    for(auto s : this->existingSensors.getRawData()) {
        if(s->getUuid() == quuid) {
            sensor = s;
            break;
        }
    }
    if(!sensor) {
        return;
    }
    QJsonDocument json = QJsonDocument::fromJson(config.toUtf8());
    if(json.isNull()) {
        return;
    }
    SensorConfig *configuration = new SensorConfig(json.object());
    this->actuatorFactory->createActuatorConfig(*actuator, *sensor, *configuration);
}
