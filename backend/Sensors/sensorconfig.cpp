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

int SensorConfig::getStart()
{
    QJsonValue v = (*this)["start"];
    return v.toInt();
}


int SensorConfig::getStop()
{
    QJsonValue v = (*this)["stop"];
    return v.toInt();
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

bool SensorConfig::ignoreOn()
{
    QString key = "ignore_on";
    QJsonValue value = (*this)[key];
    if(value.isNull()){
        return false;
    }
    return value.toBool();
}

bool SensorConfig::ignoreOff()
{
    QString key = "ignore_off";
    QJsonValue value = (*this)[key];
    if(value.isNull()){
        return false;
    }
    return value.toBool();
}

int SensorConfig::getLimit()
{
    QJsonValue v = (*this)["limit"];
    return v.toInt(0);
}

int SensorConfig::getCooldown()
{
    QJsonValue v = (*this)["cooldown"];
    return v.toInt(0);
}


QString SensorConfig::toString()
{

    QJsonObject *obj = this;
    QJsonDocument doc(*obj);
    return QString(doc.toJson(QJsonDocument::Compact));

}
