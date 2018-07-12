#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "logic/actuatorlist.h"
#include "logic/gpiomanager.h"
#include "logic/gpiolist.h"

int main(int argc, char *argv[])
{
    QQuickStyle::setStyle("Material");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //Eigener Code atm hier:
    GPIOManager manager;
    GPIOList available;
    GPIOList unavailable;
    ActuatorList actuators;
    manager.getAvailable(&available);
    manager.getUnvailable(&unavailable);
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("availablePins", &available);
    context->setContextProperty("unavailablePins", &unavailable);
    context->setContextProperty("actuators", &actuators);


    //Ende eigener Code
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
