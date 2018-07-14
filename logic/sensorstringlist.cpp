#include "sensorstringlist.h"

SensorStringList::SensorStringList(QObject *parent)
    : QAbstractListModel(parent)
{
}

void SensorStringList::setSensorStringList(QStringList list)
{
    this->stringList = list;
    this->stringList.sort();
}

QVariant SensorStringList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

int SensorStringList::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return this->stringList.count();
}

QVariant SensorStringList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    return QVariant(this->stringList.at(index.row()));
}

QString SensorStringList::at(int index)
{
    return this->stringList.at(index);
}
