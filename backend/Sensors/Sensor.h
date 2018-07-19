#ifndef SENSOR_H
#define SENSOR_H


#include <wiringPi.h>
#include <bcm2835.h>
#include <string.h>
#include <QTimer>
#include <QUuid>
#include <QString>
#include "sensorbasetype.h"
#include <QTime>

typedef enum sensor_type_t
{
    SENSOR_TYPE_LIGHT                 = (1),
    SENSOR_TYPE_RELATIVE_HUMIDITY     = (2),
    SENSOR_TYPE_TEMPERATURE           = (3),
    SENSOR_TYPE_UV                    = (4),
    SENSOR_TYPE_IRTEMPERATURE         = (5),
    SENSOR_TYPE_MOISTURE              = (6),
    SENSOR_TYPE_CAMERA                = (7),
    SENSOR_TYPE_CLOCK                 = (8)
} sensors_type_t;

/** struct sensor_event_s is used to provide a single sensor event in a common format. */
typedef struct
{
    int32_t version;                          /**< must be sizeof(struct sensors_event_t) */
    QUuid sensor_id;                        /**< unique sensor identifier */
    int32_t type;                             /**< sensor type */
    int32_t reserved0;                        /**< reserved */
    QTime timestamp;                        /**< QTime of day */
    union
    {
        float           temperature;          /**< temperature is in degrees centigrade (Celsius) */
        float           light;                /**< light in SI lux units */
        float           relative_humidity;    /**< relative humidity in percent */
        float           voltage;              /**< voltage in volts (V) */
        float           uv;                   /**< UV light value */
        float           irTemperature;        /** IR Temperatur */
        float           moisture;             /** Substrate Humidity */
    };
} sensors_event_t;




class Sensor: public QTimer {
    Q_OBJECT
    Q_PROPERTY(QString name READ toString)
    Q_PROPERTY(QString interval READ getInterval)
    Q_PROPERTY(QString uuid READ getId)

public:
    Sensor(int);
    virtual ~Sensor() {}
    virtual bool getEvent(sensors_event_t*) = 0;
    virtual sensors_type_t getType() const = 0;
    virtual QString getSort() = 0;
    virtual SensorBaseType getRawType() = 0;
    Q_INVOKABLE virtual const QString& toString();
    Q_INVOKABLE int getInterval();
    void setInterval(int inerval);
    QUuid getUuid();
    Q_INVOKABLE QString getId();
    QList<qreal> getEventValueLog();
    float getLastEventValue();



public slots:
    void intervallElapsed();

signals:
    void newSensorEvent(sensors_event_t*);

protected:
    QUuid _id;
    int _interval;
    QString name;
    QList<qreal> eventValueLog;

private:
    void fillLog(float val);
    void logEvent(sensors_event_t*);
    int lastCheckedHour;


};

#endif
