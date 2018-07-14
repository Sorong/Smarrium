#ifndef GPIOMANAGER_H
#define GPIOMANAGER_H
#include <QSharedPointer>
#include <QList>
#include <logic/gpiolist.h>
#include "gpiomap.h"
#include "logic/gpio.h"

class GPIOManager : public QObject
{
Q_OBJECT
public:
    GPIOManager();
    virtual ~GPIOManager();
    GPIOList* getAvailable(GPIOList*);
    GPIOList* getUnavailable(GPIOList*);
    QString pinToString(GPIO);
    GPIO stringToPin(const QString&);
signals:
    void addAvailable(const QString str);
    void addUnavailable(const QString str);
public slots:
    void availableChanged(const QString str);
    void unavailableChanged(const QString str);
private:
    GPIOList* getGPIOList(GPIOList*, bool available);
    QList<GPIO> available;
    QList<GPIO> unavailable;
    GPIOMap map;
};

#endif // GPIOMANAGER_H
