#ifndef SENSORCONFIG_H
#define SENSORCONFIG_H

#include <QJsonObject>



class SensorConfig : public QJsonObject
{
public:
    SensorConfig(QJsonObject json);
    float getMinValue();
    float getMaxValue();
};

#endif // SENSORCONFIG_H
