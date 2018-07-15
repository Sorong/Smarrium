#include "configfactory.h"

ConfigFactory::ConfigFactory(QObject *parent) : QObject(parent)
{

}

QString ConfigFactory::getConfig(SensorBaseType type)
{
    return "{}";
}
