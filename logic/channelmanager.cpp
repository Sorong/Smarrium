#include <QDebug>
#include <QObject>
#include "channelmanager.h"
#include "channelmap.h"

ChannelManager::ChannelManager() :
    available({
              CHANNEL::CHANNEL_0,
              CHANNEL::CHANNEL_1,
              CHANNEL::CHANNEL_2,
              CHANNEL::CHANNEL_3,
              CHANNEL::CHANNEL_4,
              CHANNEL::CHANNEL_5,
              CHANNEL::CHANNEL_6,
              CHANNEL::CHANNEL_7
              })
{

}

ChannelManager::~ChannelManager() {

}


ChannelList* ChannelManager::getAvailable(ChannelList *ptr) {
    if(!ptr) {
        return nullptr;
    }
    connect(ptr, &ChannelList::removed, this, &ChannelManager::availableChanged);
    connect(this, &ChannelManager::addAvailable, ptr, &ChannelList::add);
    return getChannelList(ptr, true);
}

ChannelList* ChannelManager::getUnavailable(ChannelList *ptr) {
    if(!ptr) {
        return nullptr;
    }
    connect(ptr,  &ChannelList::removed, this, &ChannelManager::unavailableChanged);
    connect(this, &ChannelManager::addUnavailable, ptr,  &ChannelList::add);
    return getChannelList(ptr, false);
}

QString ChannelManager::pinToString(CHANNEL channel)
{
    return this->map[channel];
}

CHANNEL ChannelManager::stringToPin(const QString& str)
{
   return this->map[str];
}

ChannelList* ChannelManager::getChannelList(ChannelList *ptr, bool available) {
    if(!ptr) {
        return nullptr;
    }
    QStringList strings;
    for(auto &channel : available ? this->available : this->unavailable) {
        QString item = pinToString(channel);
        if(item.size() > 0) {
            strings.append(item);
        }
    }
    ptr->setChannelList(strings);
    return ptr;
}

void ChannelManager::availableChanged(QString str) {
    emit addUnavailable(str);
    qDebug() << "availableChanged" << str;
}

void ChannelManager::unavailableChanged(QString str) {
    qDebug() << "unavailableChanged" << str;
}
