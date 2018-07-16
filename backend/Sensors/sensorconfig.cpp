#include "sensorconfig.h"

#include <QJsonDocument>

SensorConfig::SensorConfig(QJsonObject json) : QJsonObject(json)
{
}

float SensorConfig::getMinValue(int time)
{
    QString key = QString::number(time);
    QJsonValue v = (*this)[key];
    v = v["min"];
    return v.toDouble();
}

float SensorConfig::getMaxValue(int time)
{
    QString key = QString::number(time);
    QJsonValue v = (*this)[key];
    v = v["max"];
    return v.toDouble();
}

QString SensorConfig::toString()
{

    QJsonObject *obj = this;
    QJsonDocument doc(*obj);
    return QString(doc.toJson(QJsonDocument::Compact));

}
