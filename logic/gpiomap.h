#ifndef GPIOMAP_H
#define GPIOMAP_H
#include "gpio.h"
#include <QMap>

class GPIOMap
{
public:
    GPIOMap();
    GPIOMap(const GPIOMap&) = delete;
    GPIOMap& operator=(const GPIOMap &other) = delete;
    const QString &operator[](const GPIO& pin);
    const GPIO &operator[](const QString& str);
private:
    void addItem(const GPIO&,const  QString&);
    QMap<GPIO, QString> mapToString;
    QMap<QString, GPIO> mapToPin;
};

#endif // GPIOMAP_H
