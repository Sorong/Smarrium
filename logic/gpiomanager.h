#ifndef GPIOMANAGER_H
#define GPIOMANAGER_H
#include <QSharedPointer>
#include <QList>
#include <logic/gpiolist.h>
#include "logic/gpio.h"



class GPIOManager : public QObject
{
Q_OBJECT
public:
    GPIOManager();
    virtual ~GPIOManager();
    GPIOList* getAvailable(GPIOList*);
    GPIOList* getUnvailable(GPIOList*);
public slots:
    void availableChanged(QString *str);
    void unavailableChanged(QString *str);
private:
    GPIOList* getGPIOList(GPIOList*, bool available);
    QList<GPIO> available;
    QList<GPIO> unavailable;
};

#endif // GPIOMANAGER_H
