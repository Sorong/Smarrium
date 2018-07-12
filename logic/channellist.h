#ifndef CHANNELLIST_H
#define CHANNELLIST_H

#include <QAbstractListModel>
#include <QStringList>
#include <QString>


class ChannelList : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ChannelList(QObject *parent = nullptr);
    ChannelList(const ChannelList&) = delete;
    ChannelList& operator=(const ChannelList &other) = delete;

    void setChannelList(const QStringList &channelList);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE bool removeAt(int index);

    Q_INVOKABLE const QString at(int index);

signals:
    void removed(const QString);
public slots:
    void add(const QString);
private:

    QStringList channelList;
};

#endif // CHANNELLIST_H
