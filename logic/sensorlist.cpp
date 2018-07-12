#include <QDebug>
#include "sensorlist.h"

SensorList::SensorList(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant SensorList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

int SensorList::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return this->sensors.count();
}

QVariant SensorList::data(const QModelIndex &index, int role) const
{
    qDebug() << "sensorList" << index.row();
    if (!index.isValid() && role == Qt::DisplayPropertyRole)
        return QVariant();
    return QVariant("??");
}

bool SensorList::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; i++) {
        sensors.insert(row, nullptr);
    }
    endInsertRows();
    return true;
}

bool SensorList::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for(int i = 0; i < count; i++) {
        Sensor* sensor = this->sensors.at(row);
        if(sensor)
            delete sensor;
        this->sensors.removeAt(row);
    }
    endRemoveRows();
    return true;
}
