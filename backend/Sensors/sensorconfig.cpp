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

bool SensorConfig::minIsOff(){
    QString key = "min_is_off";
    QJsonValue value = (*this)[key];
    if(value.isNull()){
        return false;
    }
    return value.toBool();
}

bool SensorConfig::ignoreSwitches(){
    QString key = "ignore";
    QJsonValue value = (*this)[key];
    if(value.isNull()){
        return false;
    }
    return value.toBool();
}

QString SensorConfig::toString()
{

    QJsonObject *obj = this;
    QJsonDocument doc(*obj);
    return QString(doc.toJson(QJsonDocument::Compact));

}
