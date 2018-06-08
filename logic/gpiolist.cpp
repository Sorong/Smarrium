#include <qdebug.h>
#include "gpiolist.h"

GPIOList::GPIOList(QObject *parent)
    : QAbstractListModel(parent)
{
}

void GPIOList::setGPIOList(const QStringList &gpioList) {
    this->gpioList = gpioList;
}

QVariant GPIOList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

int GPIOList::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return gpioList.count();
}

QVariant GPIOList::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && role == Qt::DisplayRole) {
        return gpioList.at(index.row());
    }
    return QVariant();
}

bool GPIOList::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for(int i = 0; i < count; i++) {
        QString item = gpioList.at(row);
        qDebug() << item;
        emit removed(item);
        this->gpioList.removeAt(row);
    }
    endRemoveRows();
    return true;
}

bool GPIOList::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; i++) {
        gpioList.insert(row, "");
    }
    endInsertRows();
    return true;
}

bool GPIOList::removeAt(int index) {
    return removeRows(index, 1);
}

const QString GPIOList::at(int index)
{
    return gpioList.at(index);
}

void GPIOList::add(const QString item)
{
    this->insertRows(gpioList.size(), 1);
    this->gpioList[gpioList.size() - 1] = item;

    qDebug() << "add " << gpioList.at(gpioList.size() - 1);
}

