#include "sensorconfig.h"

#include <QJsonDocument>

SensorConfig::SensorConfig(QJsonObject json) : QJsonObject(json)
{
}

float SensorConfig::getMinValue()
{
    return 0; //TODO: Logik
}

float SensorConfig::getMaxValue()
{
    return 50; //TODO: Logik
}

QString SensorConfig::toString()
{
    QJsonObject *obj = this;
    QJsonDocument doc(*obj);
    return QString(doc.toJson(QJsonDocument::Compact));
}
