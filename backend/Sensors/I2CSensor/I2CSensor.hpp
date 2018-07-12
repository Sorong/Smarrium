#include "./../Sensor.h"

typedef struct
{
    char     name[12];                        /**< sensor name */
    int32_t  version;                         /**< version of the hardware + driver */
    int32_t  sensor_id;                       /**< unique sensor identifier */
    int32_t  type;                            /**< this sensor's type (ex. SENSOR_TYPE_LIGHT) */
    int8_t  adress;                         /**< Connectet Channel on MSP3008 ADC */
} sensor_I2C_t;

class I2CSensor{

public: 
    I2CSensor(){}
    ~I2CSensor(){}

    virtual int getAdress() = 0;
    virtual void setAdress(int) = 0;
    virtual void getI2CSensor(sensor_I2C_t*) = 0;
};
