#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H


#include <QUuid>
#include "./../Sensor.h"

typedef struct
{
    char     name[12];                        /**< sensor name */
    int32_t  version;                         /**< version of the hardware + driver */
    QUuid  sensor_id;                          /**< unique sensor identifier */
    int32_t  type;                            /**< this sensor's type (ex. SENSOR_TYPE_LIGHT) */
    int32_t  channel;                         /**< Connectet Channel on MSP3008 ADC */
} sensor_analog_t;

class AnalogSensor{

public: 
    AnalogSensor(){}
    ~AnalogSensor(){}

    virtual uint8_t getChannel() = 0;
    virtual void setChannel(uint8_t) = 0;
    virtual void getAnalogSensor(sensor_analog_t*) = 0;
};


#endif
