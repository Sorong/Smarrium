#ifndef SENSOR_H
#define SENSOR_H


#include <wiringPi.h>
#include <bcm2835.h>
#include <string.h>
#include <QTimer>
#include <QUuid>


typedef enum sensor_type_t
{
    SENSOR_TYPE_LIGHT                 = (1),
    SENSOR_TYPE_RELATIVE_HUMIDITY     = (2),
    SENSOR_TYPE_TEMPERATURE           = (3),
    SENSOR_TYPE_UV                    = (4),
    SENSOR_TYPE_IRTEMPERATURE         = (5),
    SENSOR_TYPE_MOISTURE              = (6)
} sensors_type_t;

/** struct sensor_event_s is used to provide a single sensor event in a common format. */
typedef struct
{
    int32_t version;                          /**< must be sizeof(struct sensors_event_t) */
    QUuid sensor_id;                        /**< unique sensor identifier */
    int32_t type;                             /**< sensor type */
    int32_t reserved0;                        /**< reserved */
    int32_t timestamp;                        /**< time is in milliseconds */
    union
    {
        float           temperature;          /**< temperature is in degrees centigrade (Celsius) */
        float           light;                /**< light in SI lux units */
        float           relative_humidity;    /**< relative humidity in percent */
        float           voltage;              /**< voltage in volts (V) */
        float           uv;                   /**< UV light value */
        float           irTemperature;
        float           moisture;

    };
} sensors_event_t;


typedef struct{

    QUuid   sensorId;
    float   minValue;
    float   maxValue;
}sensor_config;

class Sensor: public QTimer {
    Q_OBJECT

public:
    Sensor(int);
    virtual ~Sensor() {}

    virtual bool getEvent(sensors_event_t*) = 0;
    virtual sensors_type_t getType() const = 0;
    QUuid getId();

public slots:
    void intervallElapsed();

signals:
    void newSensorEvent(sensors_event_t*);

protected:
    QUuid _id;

};

#endif
