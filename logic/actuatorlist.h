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
    enum Roles {
        TypeRole = Qt::UserRole + 1,
        CodeRole
    };
    explicit ActuatorList(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int, QByteArray> roleNames() const override;


    void addActuator(const QSharedPointer<Actuator> actuator);

    Q_INVOKABLE const Actuator& at(int index);

    Q_INVOKABLE bool removeAt(int index);

    Q_INVOKABLE bool isEmpty();

public slots:
    void selectActuator(int index);

signals:
    void onSelect(Actuator*);


private:
    QList<QSharedPointer<Actuator>> actuators;
    GPIOMap gpioMap;
    RCSwitch sender;
};

#endif // ACTUATORLIST_H
