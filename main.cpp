#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "backend/Actuator/actuatorcamera.h"

#include "logic/qmlcontextmanager.h"

int main(int argc, char *argv[])
{
    wiringPiSetup();
    ActuatorCamera camera;
    camera.takePicture();
    camera.retriveDifferencePicture();
    QQuickStyle::setStyle("Material");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qRegisterMetaType<SensorBaseType>("SensorBaseType");
    qmlRegisterUncreatableType<BaseType>("SensorBaseType", 1, 0, "SensorBaseType", "Not creatable as it is an enum type");

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QMLContextManager manager(engine);
    manager.init();
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
