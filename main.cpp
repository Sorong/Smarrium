#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include <backend/Actuator/actuatorcamera.h>

#include "logic/qmlcontextmanager.h"
#include "./backend/Actuator/actuatorcamera.h"

int main(int argc, char *argv[])
{
    wiringPiSetup();
    ActuatorCamera camera;
    camera.takePicture();
    QQuickStyle::setStyle("Material");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QMLContextManager manager(engine);
    manager.init();
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
