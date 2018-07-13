#ifndef SENSORSTRINGLIST_H
#define SENSORSTRINGLIST_H

#include <QAbstractListModel>

class SensorStringList : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SensorStringList(QObject *parent = nullptr);
    void setSensorStringList(QStringList list);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QStringList stringList;
};

#endif // SENSORSTRINGLIST_H
