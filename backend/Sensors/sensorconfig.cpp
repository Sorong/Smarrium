#include "sensorconfig.h"

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
