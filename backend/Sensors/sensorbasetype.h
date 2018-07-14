#ifndef SENSORBASETYPE_H
#define SENSORBASETYPE_H
#include <QObject>
//siehe https://github.com/ndesai/qml.guide/tree/master/examples/QtQmlEnums für dieses Hexenwerk
class BaseType
{
    Q_GADGET
public:
    enum Type {
        UV,
        LIGHT,
        TEMPERATURE,
        HUMIDITY
    };
    Q_ENUM(Type)
private:
    explicit BaseType();
};
typedef BaseType::Type SensorBaseType;

#endif // SENSORBASETYPE_H
