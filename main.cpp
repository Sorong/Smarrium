#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "backend/Sensors/VirtualSensor/Camera/camera.h"

#include "logic/qmlcontextmanager.h"

int main(int argc, char *argv[])
{
    wiringPiSetup();
    QQuickStyle::setStyle("Material");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qRegisterMetaType<SensorBaseType>("SensorBaseType");
    qmlRegisterUncreatableType<BaseType>("SensorBaseType", 1, 0, "SensorBaseType", "Not creatable as it is an enum type");

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationPath", "file://"+qApp->applicationDirPath()+ "/");
    QMLContextManager manager(engine);
    manager.init();
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
