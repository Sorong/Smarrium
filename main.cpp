#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "logic/actuatorlist.h"
#include "logic/gpiomanager.h"
#include "logic/channelmanager.h"
#include "logic/gpiolist.h"
#include "factories/sensor_factory.h"
#include "factories/actuator_factory.h"
#include "backend/Actuator/actuatorcamera.h"

int main(int argc, char *argv[])
{
    wiringPiSetup();
    ActuatorCamera camera;
    camera.takePicture();
    QQuickStyle::setStyle("Material");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //Eigener Code atm hier:
    GPIOManager manager;
    ChannelManager channelManager;
    ChannelList availableChannels;
    ChannelList unavailableChannels;
    GPIOList available;
    GPIOList unavailable;
    SensorList sensors;
    ActuatorList actuators;
    ActuatorFactory actuatorFactory(actuators);
    SensorStringList supportedSensors;
    SensorFactory sensorFactory(available, sensors);
    sensorFactory.getSensorTypes(&supportedSensors);
    manager.getAvailable(&available);
    manager.getUnavailable(&unavailable);
    channelManager.getAvailable(&availableChannels);
    channelManager.getUnavailable(&unavailableChannels);

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("availablePins", &available);
    context->setContextProperty("unavailablePins", &unavailable);
    context->setContextProperty("actuators", &actuators);
    context->setContextProperty("actuatorFactory", &actuatorFactory);
    context->setContextProperty("sensorFactory", &sensorFactory);
    context->setContextProperty("supportedSensors", &supportedSensors);
    context->setContextProperty("availableChannels", &availableChannels);
    context->setContextProperty("existingSensors", &sensors);

    //Ende eigener Code
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
