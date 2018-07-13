#ifndef CHANNELMANAGER_H
#define CHANNELMANAGER_H

#include <QSharedPointer>
#include <QList>
#include <logic/channellist.h>
#include "channelmap.h"
#include "logic/channel.h"

class ChannelManager : public QObject
{
Q_OBJECT
public:
    ChannelManager();
    virtual ~ChannelManager();
    ChannelList* getAvailable(ChannelList*);
    ChannelList* getUnavailable(ChannelList*);
    QString pinToString(CHANNEL);
    CHANNEL stringToPin(const QString&);
signals:
    void addAvailable(const QString str);
    void addUnavailable(const QString str);
public slots:
    void availableChanged(const QString str);
    void unavailableChanged(const QString str);
private:
    ChannelList* getChannelList(ChannelList*, bool available);
    QList<CHANNEL> available;
    QList<CHANNEL> unavailable;
    ChannelMap map;
};


#endif // CHANNELMANAGER_H
