#include "sensorconfig.h"

SensorConfig::SensorConfig(QJsonObject json) : QJsonObject(json)
{
}

float SensorConfig::getMinValue()
{
    int currentHour = QTime::currentTime().hour();
    QJsonArray configList = this->operator []("config");
    float min = (float) configList[currentHour][currentHour+""]["min"].toDouble();
    return min;
}

float SensorConfig::getMaxValue()
{
    int currentHour = QTime::currentTime().hour();
    QJsonArray configList = this->operator []("config");
    float max = (float) configList[currentHour][currentHour+""]["max"].toDouble();
    return max;
}
