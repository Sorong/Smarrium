#include <QDebug>
#include <QObject>
#include "gpiomanager.h"

GPIOManager::GPIOManager() :
    available({
              GPIO::GPIO_0,
              GPIO::GPIO_1,
              GPIO::GPIO_2
              })
{

}

GPIOManager::~GPIOManager() {

}


GPIOList* GPIOManager::getAvailable(GPIOList *ptr) {
    if(!ptr) {
        return nullptr;
    }
    connect(ptr, SIGNAL(removed(QString *)), this, SLOT(availableChanged(QString*)));
    return getGPIOList(ptr, true);
}

GPIOList* GPIOManager::getUnvailable(GPIOList *ptr) {
    if(!ptr) {
        return nullptr;
    }
    connect(ptr, SIGNAL(removed(QString *)), this, SLOT(unavailableChanged(QString*)));
    return getGPIOList(ptr, false);
}

GPIOList* GPIOManager::getGPIOList(GPIOList *ptr, bool available) {
    if(!ptr) {
        return nullptr;
    }
    QStringList strings;
    for(auto &gpio : available ? this->available : this->unavailable) {
        switch(gpio) {
        case GPIO_0:
            strings.append("GPIO_0");
            break;
        case GPIO_1:
            strings.append("GPIO_1");
            break;
        case GPIO_2:
            strings.append("GPIO_2");
            break;
        }
    }
    strings.append("C++ Inputs");
    ptr->setGPIOList(strings);
    return ptr;
}

void GPIOManager::availableChanged(QString *str) {
    qDebug() << "availableChanged";
}
void GPIOManager::unavailableChanged(QString *str) {
    qDebug() << "unavailableChanged";
}
