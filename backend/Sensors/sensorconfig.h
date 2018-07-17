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
    float getMinValue(int );
    float getMaxValue(int );
    int getStart();
    int getStop();
    bool minIsOff();
    bool ignoreSwitches();
    QString toString();
};

#endif // SENSORCONFIG_H
