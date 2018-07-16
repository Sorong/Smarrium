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
        LUX,
        TEMPERATURE,
        REL_HUMIDITY,
        SUBSTRAT_HUMIDITY,
        CLOCK,
        CAMERA
    };
    Q_ENUM(Type)
private:
    explicit BaseType();
};
typedef BaseType::Type SensorBaseType;

#endif // SENSORBASETYPE_H
