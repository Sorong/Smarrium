#ifndef SENSORFACTORY_H
#define SENSORFACTORY_H

#include <QObject>

class SensorFactory : public QObject
{
    Q_OBJECT
public:
    explicit SensorFactory(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SENSORFACTORY_H