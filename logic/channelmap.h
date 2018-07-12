#ifndef CHANNELMAP_H
#define CHANNELMAP_H



#include "channel.h"
#include <QMap>

class ChannelMap
{
public:
    ChannelMap();
    ChannelMap(const ChannelMap&) = delete;
    ChannelMap& operator=(const ChannelMap &other) = delete;
    const QString &operator[](const CHANNEL& pin);
    const CHANNEL &operator[](const QString& str);
private:
    void addItem(const CHANNEL&,const  QString&);
    QMap<CHANNEL, QString> mapToString;
    QMap<QString, CHANNEL> mapToPin;
};

#endif // ChannelMap_H
