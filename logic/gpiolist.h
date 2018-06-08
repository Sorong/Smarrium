#ifndef GPIOLIST_H
#define GPIOLIST_H

#include <QAbstractListModel>
#include <QStringList>

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

    bool removeRow(int row, const QModelIndex &parent = QModelIndexList()) const override;
signals:
    void removed(QString *);
private:

    QStringList gpioList;
};

#endif // GPIOLIST_H
