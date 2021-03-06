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
        UuidRole,
        LogRole,
        LastRole,
        IndexRole,
        SensorIntervalRole
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

    const QList<Sensor*>& getRawData();

public slots:
    void selectSensor(int index);

    void add(Sensor* sensor);

    void addUnique(Sensor* sensor);

    void removeAt(int index);

    Q_INVOKABLE bool isEmpty();

    void changeConfig(QString uuid, QString config);

signals:
    void onSelect(Sensor* sensor);
    void onChangeConfig(QString uuid, QString config);
    void onRemove(Sensor* sensor);


private:
     QList<Sensor*> sensorList;
};

#endif // SENSORLIST_H
