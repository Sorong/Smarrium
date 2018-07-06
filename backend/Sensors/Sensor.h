#ifndef SENSOR_H
#define SENSOR_H


#include <wiringPi.h>
#include <bcm2835.h>
#include <string.h>
#include <QTimer>


typedef enum
{
  SENSOR_TYPE_ACCELEROMETER         = (1),   /**< Gravity + linear acceleration */
  SENSOR_TYPE_MAGNETIC_FIELD        = (2),
  SENSOR_TYPE_ORIENTATION           = (3),
  SENSOR_TYPE_GYROSCOPE             = (4),
  SENSOR_TYPE_LIGHT                 = (5),
  SENSOR_TYPE_PRESSURE              = (6),
  SENSOR_TYPE_PROXIMITY             = (8),
  SENSOR_TYPE_GRAVITY               = (9),
  SENSOR_TYPE_LINEAR_ACCELERATION   = (10),  /**< Acceleration not including gravity */
  SENSOR_TYPE_ROTATION_VECTOR       = (11),
  SENSOR_TYPE_RELATIVE_HUMIDITY     = (12),
  SENSOR_TYPE_TEMPERATURE           = (13),
  SENSOR_TYPE_VOLTAGE               = (15),
  SENSOR_TYPE_CURRENT               = (16),
  SENSOR_TYPE_COLOR                 = (17),
  SENSOR_TYPE_UV                    = (18),
  SENSOR_TYPE_IRTEMPERATURE         = (19),
  SENSOR_TYPE_MOISTURE              = (20)
} sensors_type_t;

/* Sensor event (36 bytes) */
/** struct sensor_event_s is used to provide a single sensor event in a common format. */
typedef struct
{
    int32_t version;                          /**< must be sizeof(struct sensors_event_t) */
    int32_t sensor_id;                        /**< unique sensor identifier */
    int32_t type;                             /**< sensor type */
    int32_t reserved0;                        /**< reserved */
    int32_t timestamp;                        /**< time is in milliseconds */
    union
    {
        float           data[4];
        float           temperature;          /**< temperature is in degrees centigrade (Celsius) */
        float           distance;             /**< distance in centimeters */
        float           light;                /**< light in SI lux units */
        float           pressure;             /**< pressure in hectopascal (hPa) */
        float           relative_humidity;    /**< relative humidity in percent */
        float           current;              /**< current in milliamps (mA) */
        float           voltage;              /**< voltage in volts (V) */
        float           uv;                   /**< UV light value */
        float           irTemperature;
        float           moisture;

    };
} sensors_event_t;


typedef struct{

    int     sensorId;
    float   minValue;
    float   maxValue;
}sensor_config;

class Sensor: public QTimer {
    Q_OBJECT

public:
  Sensor(int);
  virtual ~Sensor() {}
  
  virtual bool getEvent(sensors_event_t*) = 0;
  //virtual void getSensor(sensor_t*) = 0;
  
 public slots:
  void intervallElapsed();

 signals:
  void newSensorEvent(sensors_event_t*);

 private:
  bool _autoRange;

};

#endif
