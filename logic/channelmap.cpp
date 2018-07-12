#include <QMap>
#include "channelmap.h".h"

ChannelMap::ChannelMap()
{
   addItem(CHANNEL_0, "1");
   addItem(CHANNEL_1, "2");
   addItem(CHANNEL_2, "3");
   addItem(CHANNEL_3, "4");
   addItem(CHANNEL_4, "5");
   addItem(CHANNEL_5, "6");
   addItem(CHANNEL_6, "7");
   addItem(CHANNEL_7, "8");
}

const QString &ChannelMap::operator[](const CHANNEL& pin)
{
    return this->mapToString[pin];
}

const CHANNEL &ChannelMap::operator[](const QString& str)
{
    return this->mapToPin[str];
}

void ChannelMap::addItem(const CHANNEL &pin, const QString& str)
{
    this->mapToPin[str] = pin;
    this->mapToString[pin] = str;
}

