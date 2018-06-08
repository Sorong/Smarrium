
#include <QMap>
#include "gpiomap.h"

GPIOMap::GPIOMap()
{
   addItem(GPIO_0, "GPIO_0");
   addItem(GPIO_1, "GPIO_1");
   addItem(GPIO_2, "GPIO_2");
}

const QString &GPIOMap::operator[](const GPIO& pin)
{
    return this->mapToString[pin];
}

const GPIO &GPIOMap::operator[](const QString& str)
{
    return this->mapToPin[str];
}

void GPIOMap::addItem(const GPIO &pin, const QString& str)
{
    this->mapToPin[str] = pin;
    this->mapToString[pin] = str;
}
