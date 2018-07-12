#ifndef DIGITALSENSOR_H
#define DIGITALSENSOR_H

#include <QUuid>
#include "./../Sensor.h"

typedef struct
{
    char     name[12];                        /**< sensor name */
    int32_t  version;                         /**< version of the hardware + driver */
    QUuid  sensor_id;                       /**< unique sensor identifier */
    int32_t  type;                            /**< this sensor's type (ex. SENSOR_TYPE_LIGHT) */
    int32_t  pin;                         /**< Connectet Channel on MSP3008 ADC */
} sensor_digital_t;

class DigitalSensor{

public: 
    DigitalSensor(){}
    ~DigitalSensor(){}

    virtual uint8_t getPin() = 0;
    virtual void setPin(uint8_t) = 0;
    virtual void getDigitalSensor(sensor_digital_t*) = 0;
};

#endif
