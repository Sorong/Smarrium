#include <QDebug>
#include <backend/Sensors/VirtualSensor/Camera/camera.h>
#include "sensorlist.h"

SensorList::SensorList(QObject *parent)
    : QAbstractListModel(parent)
{
}

SensorList::~SensorList()
{
    for(auto p : this->sensorList) {
        if(p)
            delete p;
    }
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

    return this->sensorList.count();
}

QVariant SensorList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() && role == Qt::DisplayPropertyRole){
        return QVariant();
    }
    Sensor *sensor = this->sensorList.at(index.row());
    if(!sensor) {
        return QVariant();;
    }
    switch(role){
    case TypeRole:
        return QVariant(sensor->getRawType());

    case NameRole:
        return QVariant(sensor->toString());

    case IntervalRole:
        return QVariant(sensor->getInterval());

    case UuidRole:
        return QVariant(sensor->getId());
    case LastRole:
        if(sensor->getRawType() == SensorBaseType::CAMERA) {
            return QVariant(static_cast<Camera*>(sensor)->getLastImage());
        }
        return QVariant(sensor->getLastEventValue());
    case LogRole:
        return QVariant::fromValue(sensor->getEventValueLog());
    }
    return QVariant();
}

QHash<int, QByteArray> SensorList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "type";
    roles[NameRole] = "name";
    roles[IntervalRole] = "interval";
    //roles[ConnectionRole] = "connection";
    roles[UuidRole] = "uuid";

    roles[LogRole] = "log";
    roles[LastRole] = "last";
    return roles;
}

const QList<Sensor *> &SensorList::getRawData()
{
    return this->sensorList;
}

void SensorList::selectSensor(int index)
{
    if(index >= 0 && index < this->sensorList.length()) {
        emit onSelect(this->sensorList.at(index));
    }
}

bool SensorList::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; i++) {
        sensorList.insert(row, nullptr);
    }
    endInsertRows();
    return true;
}

bool SensorList::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for(int i = 0; i < count; i++) {
        Sensor* sensor = this->sensorList.at(row);
        if(sensor)
            delete sensor;
        this->sensorList.removeAt(row);
    }
    endRemoveRows();
    return true;
}

void SensorList::add(Sensor *sensor)
{
    if(!sensor) {
        return;
    }
    this->insertRows(sensorList.size(), 1);
    this->sensorList[sensorList.size() - 1] = sensor;

    qDebug() << "add Sensor:  " << sensorList.at(sensorList.size() - 1);
}

void SensorList::addUnique(Sensor *sensor)
{
    if(!sensor) {
        return;
    }
    for(auto s : this->sensorList) {
        if(s->getId() == sensor->getId()) {
            return;
        }
    }
    this->add(sensor);
}

bool SensorList::isEmpty()
{
    return this->sensorList.isEmpty();
}

void SensorList::changeConfig(QString uuid, QString config)
{
    emit onChangeConfig(uuid, config);
}
