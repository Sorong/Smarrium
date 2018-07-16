#ifndef SENSORCONFIG_H
#define SENSORCONFIG_H

#include <QJsonObject>
#include <QTime>
#include <QJsonArray>
#include <QJsonValue>



class SensorConfig : public QJsonObject
{
public:
    SensorConfig(QJsonObject json);
    float getMinValue();
    float getMaxValue();
};

#endif // SENSORCONFIG_H
