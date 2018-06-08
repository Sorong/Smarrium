#ifndef GPIOLIST_H
#define GPIOLIST_H

#include <QAbstractListModel>
#include <QStringList>
#include <QString>

//See: http://www.java2s.com/Code/Cpp/Qt/stringlistmodelexample.htm
class GPIOList : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit GPIOList(QObject *parent = nullptr);
    GPIOList(const GPIOList&) = delete;
    GPIOList& operator=(const GPIOList &other) = delete;

    void setGPIOList(const QStringList &gpioList);

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

    QStringList gpioList;
};

#endif // GPIOLIST_H
