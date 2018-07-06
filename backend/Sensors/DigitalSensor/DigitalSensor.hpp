#include "./../Sensor.h"

#include "./../Sensor.h"

typedef struct
{
    char     name[12];                        /**< sensor name */
    int32_t  version;                         /**< version of the hardware + driver */
    int32_t  sensor_id;                       /**< unique sensor identifier */
    int32_t  type;                            /**< this sensor's type (ex. SENSOR_TYPE_LIGHT) */
    int32_t  pin;                         /**< Connectet Channel on MSP3008 ADC */
} sensor_digital_t;

class DigitalSensor{

public: 
    DigitalSensor(){}
    ~DigitalSensor(){}

    virtual int getChannel() = 0;
    virtual void setChannel(int) = 0;
    virtual void getAnalogSensor(sensor_digital_t*) = 0;
};
