#ifndef ACTUATORLIST_H
#define ACTUATORLIST_H

#include <QAbstractListModel>
#include <QList>
#include <QSharedPointer>
#include "backend/RCSwitch/RCSwitch.h"
#include "backend/Actuator/Actuator.hpp"
#include "logic/gpiomap.h"

class ActuatorList : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ActuatorList(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE void addActuator(const QString&);

    Q_INVOKABLE void setSender(const QString gpioString);

private:
    QList<QSharedPointer<Actuator>> actuators;
    GPIOMap gpioMap;
    RCSwitch sender;
};

#endif // ACTUATORLIST_H
