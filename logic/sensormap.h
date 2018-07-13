#ifndef SENSORMAP_H
#define SENSORMAP_H
#include <QMap>
#include "backend/Sensors/Sensor.h"



class QString;
class SensorMap
{
public:
    SensorMap();
    SensorMap(const SensorMap&) = delete;
    SensorMap& operator=(const SensorMap &other) = delete;
    const QString &operator[](const sensor_type_t& type);
    const sensor_type_t &operator[](const QString& str);
    QStringList getTypes();

private:
    void addItem(const sensors_type_t &type,const  QString &str);
    QMap<sensors_type_t, QString> mapToString;
    QMap<QString, sensors_type_t> mapToSensor;
};

#endif // SENSORMAP_H
