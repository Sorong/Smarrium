#ifndef I2CSENSOR_H
#define I2CSENSOR_H


#include "./../Sensor.h"

typedef struct
{
    char     name[12];                        /**< sensor name */
    int32_t  version;                         /**< version of the hardware + driver */
    QUuid  sensor_id;                       /**< unique sensor identifier */
    int32_t  type;                            /**< this sensor's type (ex. SENSOR_TYPE_LIGHT) */
    int8_t  address;                         /**< Connectet Channel on MSP3008 ADC */
} sensor_I2C_t;

class I2CSensor{

public: 
    I2CSensor(){}
    ~I2CSensor(){}

    virtual uint8_t getAddress() = 0;
    virtual void setAddress(uint8_t) = 0;
    virtual void getI2CSensor(sensor_I2C_t*) = 0;
};


#endif
