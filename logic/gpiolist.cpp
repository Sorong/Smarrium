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
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
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

bool GPIOList::removeRow(int row, const QModelIndex &parent) const
{
    this->gpioList.removeAt(row);
    return true;
}
