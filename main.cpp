#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "logic/gpiomanager.h"
#include "logic/gpiolist.h"
//#include "frontend/example.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //Eigener Code atm hier:
    GPIOManager manager;
    GPIOList available;
    GPIOList unavailable;
    manager.getAvailable(&available);
    manager.getUnvailable(&unavailable);
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("availablePins", &available);
    context->setContextProperty("unavailablePins", &unavailable);


    //Ende eigener Code
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
