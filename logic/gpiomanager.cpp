#include <QDebug>
#include <QObject>
#include "gpiomanager.h"
#include "gpiomap.h"

GPIOManager::GPIOManager() :
    available({
              GPIO::GPIO_7
              })
{

}

GPIOManager::~GPIOManager() {

}


GPIOList* GPIOManager::getAvailable(GPIOList *ptr) {
    if(!ptr) {
        return nullptr;
    }
    connect(ptr, SIGNAL(removed(QString)), this, SLOT(availableChanged(QString)));
    connect(this, SIGNAL(addAvailable(QString)), ptr, SLOT(add(QString)));
    return getGPIOList(ptr, true);
}

GPIOList* GPIOManager::getUnvailable(GPIOList *ptr) {
    if(!ptr) {
        return nullptr;
    }
    connect(ptr, SIGNAL(removed(QString)), this, SLOT(unavailableChanged(QString)));
    connect(this, SIGNAL(addUnavailable(QString)), ptr, SLOT(add(QString)));
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
    strings.append("C++ Inputs");
    ptr->setGPIOList(strings);
    return ptr;
}

void GPIOManager::availableChanged(QString str) {
    emit addUnavailable(str);
    qDebug() << "availableChanged";
}

void GPIOManager::unavailableChanged(QString str) {
    qDebug() << "unavailableChanged";
}
