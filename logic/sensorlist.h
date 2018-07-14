#ifndef SENSORLIST_H
#define SENSORLIST_H

#include <QAbstractListModel>
#include "backend/Sensors/Sensor.h"
#include "logic/sensormap.h"

class SensorList : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        TypeRole = Qt::UserRole + 1,
        NameRole,
        IntervalRole,
        UuidRole
    };

    explicit SensorList(QObject *parent = nullptr);

    ~SensorList();

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

public slots:
    void selectSensor(int index);

    void add(Sensor* sensor);

    void addUnique(Sensor* sensor);

    Q_INVOKABLE bool isEmpty();

signals:
    void onSelect(Sensor* sensor);

private:
     QList<Sensor*> sensorList;
};

#endif // SENSORLIST_H
