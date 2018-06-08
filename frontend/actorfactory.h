#ifndef ACTORFACTORY_H
#define ACTORFACTORY_H

#include <QObject>

class ActorFactory : public QObject
{
    Q_OBJECT
public:
    explicit ActorFactory(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ACTORFACTORY_H