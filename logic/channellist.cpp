#include <qdebug.h>
#include "channellist.h"

ChannelList::ChannelList(QObject *parent): QAbstractListModel(parent)
{
}


void ChannelList::setChannelList(const QStringList &channelList) {
    this->channelList = channelList;
}

QVariant ChannelList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

int ChannelList::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return channelList.count();
}

QVariant ChannelList::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && role == Qt::DisplayRole) {
        return channelList.at(index.row());
    }
    return QVariant();
}

bool ChannelList::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for(int i = 0; i < count; i++) {
        QString item = channelList.at(row);
        qDebug() << item;
        emit removed(item);
        this->channelList.removeAt(row);
    }
    endRemoveRows();
    return true;
}

bool ChannelList::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; i++) {
        channelList.insert(row, "");
    }
    endInsertRows();
    return true;
}

bool ChannelList::removeAt(int index) {
    return removeRows(index, 1);
}

const QString ChannelList::at(int index)
{
    return channelList.at(index);
}

void ChannelList::add(const QString item)
{
    this->insertRows(channelList.size(), 1);
    this->channelList[channelList.size() - 1] = item;

    qDebug() << "add " << channelList.at(channelList.size() - 1);
}
