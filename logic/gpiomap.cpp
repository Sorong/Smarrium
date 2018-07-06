
#include <QMap>
#include "gpiomap.h"

GPIOMap::GPIOMap()
{
   addItem(GPIO_7, "GPIO_7");
   addItem(GPIO_11, "GPIO_11");
   addItem(GPIO_12, "GPIO_12");
   addItem(GPIO_13, "GPIO_13");
   addItem(GPIO_15, "GPIO_15");
   addItem(GPIO_16, "GPIO_16");
   addItem(GPIO_18, "GPIO_18");
   addItem(GPIO_22, "GPIO_22");
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
