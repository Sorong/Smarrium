#include <QDebug>
#include <QObject>
#include "gpiomanager.h"
#include "gpiomap.h"

GPIOManager::GPIOManager() :
    available({
              GPIO::GPIO_7,
              //GPIO::GPIO_11,
              GPIO::GPIO_12,
              GPIO::GPIO_13,
              GPIO::GPIO_15,
              GPIO::GPIO_16,
              GPIO::GPIO_18,
              GPIO::GPIO_22
              })
{

}

GPIOManager::~GPIOManager() {

}

GPIOList* GPIOManager::getAvailable(GPIOList *ptr) {
    if(!ptr) {
        return nullptr;
    }
    connect(ptr, &GPIOList::removed, this, &GPIOManager::availableChanged);
    connect(this, &GPIOManager::addAvailable, ptr, &GPIOList::add);
    return getGPIOList(ptr, true);
}

GPIOList* GPIOManager::getUnavailable(GPIOList *ptr) {
    if(!ptr) {
        return nullptr;
    }
    connect(ptr,  &GPIOList::removed, this, &GPIOManager::unavailableChanged);
    connect(this, &GPIOManager::addUnavailable, ptr,  &GPIOList::add);
    return getGPIOList(ptr, false);
}

QString GPIOManager::pinToString(GPIO gpio)
{
    return this->map[gpio];
}

GPIO GPIOManager::stringToPin(const QString& str)
{
   return this->map[str];
}

GPIOList* GPIOManager::getGPIOList(GPIOList *ptr, bool available) {
    if(!ptr) {
        return nullptr;
    }
    QStringList strings;
    for(auto &gpio : available ? this->available : this->unavailable) {
        QString item = pinToString(gpio);
        if(item.size() > 0) {
            strings.append(item);
        }
    }
    ptr->setGPIOList(strings);
    return ptr;
}

void GPIOManager::availableChanged(QString str) {
    emit addUnavailable(str);
    qDebug() << "availableChanged" << str;
}

void GPIOManager::unavailableChanged(QString str) {
    qDebug() << "unavailableChanged" << str;
}
