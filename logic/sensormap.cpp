#include <QDebug>
#include "sensormap.h"

SensorMap::SensorMap()
{
    addItem(SENSOR_TYPE_LIGHT, "Lichtsensor");
    addItem(SENSOR_TYPE_RELATIVE_HUMIDITY, "Hygrometer");
    addItem(SENSOR_TYPE_TEMPERATURE, "Thermometer");
    addItem(SENSOR_TYPE_UV, "UV-Messer");
    addItem(SENSOR_TYPE_IRTEMPERATURE, "Infrarot-Thermometer");
    addItem(SENSOR_TYPE_MOISTURE, "Substrat-Hygrometer");
}

const QString &SensorMap::operator[](const sensor_type_t &type)
{
    return this->mapToString[type];
}

const sensor_type_t &SensorMap::operator[](const QString &str)
{
    return this->mapToSensor[str];
}

void SensorMap::addItem(const sensors_type_t &type, const QString &str)
{
    this->mapToSensor[str] = type;
    this->mapToString[type] = str;
}

QStringList SensorMap::getTypes() {
    return QStringList(this->mapToString.values());
}
