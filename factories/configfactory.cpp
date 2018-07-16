#include "configfactory.h"

#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <qjsondocument.h>
#include <qtextstream.h>

ConfigFactory::ConfigFactory(QObject *parent) : QObject(parent)
{

}

QString ConfigFactory::getConfig(SensorBaseType type)
{
    return this->readFromFile(type);
}

QString ConfigFactory::readFromFile(SensorBaseType type)
{
    QFile *file;
    switch (type) {
    case SensorBaseType::LUX:
        file = new QFile(":/configs/defaultconfigs/lux.json");
        break;
    case SensorBaseType::UV:
        file = new QFile(":/configs/defaultconfigs/uv.json");
        break;
    case SensorBaseType::TEMPERATURE:
        file = new QFile(":/configs/defaultconfigs/temperature.json");
        break;
    case SensorBaseType::REL_HUMIDITY:
        file = new QFile(":/configs/defaultconfigs/rel_humidity.json");
        break;
    case SensorBaseType::SUBSTRAT_HUMIDITY:
        file = new QFile(":/configs/defaultconfigs/substrat_humidity.json");
        break;
    case SensorBaseType::CLOCK:
        file = new QFile(":/configs/defaultconfigs/clock.json");
        break;
    case SensorBaseType::CAMERA:
        return "{}";
    default:
        return "{}";
    }
    if(!file->open(QIODevice::ReadOnly)) {
        delete file;
        return "{}";
    }
    QString out;
    QTextStream in(file);
    while(!in.atEnd()) {
        out = in.readAll();
    }
    out.remove(QRegExp("[\\n\\t\\r]"));
    qDebug() << out;
    file->close();
    delete file;
    QJsonDocument jsonFile = QJsonDocument::fromJson(out.toUtf8());
    QString s(jsonFile.toJson(QJsonDocument::Compact));
    return s;
}


