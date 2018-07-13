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
    qDebug() << "actuatorlist" << index.row();
    if (!index.isValid() && role == Qt::DisplayPropertyRole)
        return QVariant();
    return QVariant(this->actuators.at(index.row())->getCode());
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

QHash<int, QByteArray> ActuatorList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "type";
    roles[CodeRole] = "code";
    return roles;
}

void ActuatorList::addActuator(const QSharedPointer<Actuator> actuator)
{
    this->insertRows(actuators.size(), 1);
    this->actuators[actuators.size() - 1] = actuator;
}

const Actuator& ActuatorList::at(int index)
{
    return *this->actuators.at(index);
}

bool ActuatorList::removeAt(int index)
{
    return removeRows(index, 1);
}
