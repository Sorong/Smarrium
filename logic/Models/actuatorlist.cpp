#include <QDebug>
#include "actuatorlist.h"

ActuatorList::ActuatorList(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant ActuatorList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

int ActuatorList::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return this->actuators.count();
}

QVariant ActuatorList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() && role == Qt::DisplayPropertyRole)
        return QVariant();

    // FIXME: Implement me!
    return QVariant(this->actuators.at(index.row()));
}

bool ActuatorList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags ActuatorList::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool ActuatorList::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; i++) {
        actuators.insert(row, QSharedPointer<Actuator>(nullptr));
    }
    endInsertRows();
    return true;
}

bool ActuatorList::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for(int i = 0; i < count; i++) {
        this->actuators.removeAt(row);
    }
    endRemoveRows();
    return true;
}

void ActuatorList::addActuator(const QString &str)
{
    this->insertRows(actuators.size(), 1);
    QSharedPointer<Actuator> ptr = QSharedPointer<Actuator>(new Actuator(str, 0, nullptr));
    this->actuators[actuators.size() - 1] = ptr;
}

void ActuatorList::setSender(const QString gpioString)
{
    qDebug() << gpioString << " set as Senderpin";
    this->sender.enableTransmit(this->gpioMap[gpioString]);
}
