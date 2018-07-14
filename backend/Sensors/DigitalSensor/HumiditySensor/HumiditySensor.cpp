#include "HumiditySensor.hpp"
#include <QDebug>

HumiditySensor::HumiditySensor(int intervall, uint8_t pin, Bcm2835Interface *wire): Sensor(intervall)
{
    _pin = pin;
    _wire = wire;
    bcm2835_gpio_fsel(_pin, BCM2835_GPIO_FSEL_INPT);
    this->calibrate();
}

HumiditySensor::~HumiditySensor(){

}

void HumiditySensor::calibrate(){
    uint8_t offset_low = _wire->read8(BASIS_ADDR, OFFSET_ADDR_LOW);
    uint8_t offset_high = _wire->read8(BASIS_ADDR, OFFSET_ADDR_HIGH);

    uint8_t sensitivity_low = _wire->read8(BASIS_ADDR, SENSITIVITY_ADDR_LOW);
    uint8_t sensitivity_high = _wire->read8(BASIS_ADDR, SENSITIVITY_ADDR_HIGH);

    _sensitivity = (((sensitivity_low) << 8) + sensitivity_high);
    _offset = (((offset_low) << 8) + offset_high);
    
}

float HumiditySensor::calculateHumidity(){
    double frequenz = readFrequenz();
    float humidity = float((_offset - frequenz) * _sensitivity) / float(4096);
    return humidity;
}

sensors_type_t HumiditySensor::getType() const
{
    return SENSOR_TYPE_RELATIVE_HUMIDITY;
}

QString HumiditySensor::getSort(){
    return this->sort;
}

QString HumiditySensor::toString(){
    return QString("Hygrometer, GPIO PIN: " + this->_pin);
}



bool HumiditySensor::getEvent(sensors_event_t* event)
{
    
    memset(event, 0, sizeof(sensors_event_t));

    event->version   = sizeof(sensors_event_t);
    event->sensor_id = _id;
    event->type      = SENSOR_TYPE_RELATIVE_HUMIDITY;
    event->timestamp = bcm2835_st_read();
    event->relative_humidity = calculateHumidity();

    if (event->relative_humidity == -2000) {
        return false;
    }
    return true;

}

void HumiditySensor::getDigitalSensor(sensor_digital_t *sensor)
{
    memset(sensor, 0, sizeof(sensor_digital_t));

    strncpy (sensor->name, "HH10D", sizeof(sensor->name) - 1);
    sensor->name[sizeof(sensor->name)- 1] = 0;
    sensor->version     = 1;
    sensor->sensor_id   = _id;
    sensor->type        = SENSOR_TYPE_RELATIVE_HUMIDITY;
    sensor->pin         = _pin;
}

float HumiditySensor::readFrequenz(){
    struct timespec t1, t2, clock_resolution;
    clock_getres(CLOCK_REALTIME, &clock_resolution);
    long difference = 0;
    long frequenz;
    long timePeekToBottom = 0;

    for(int cycle = 0; cycle < AVERAGE_READING; cycle++){
        while(bcm2835_gpio_lev(_pin) == LOW){

        }
        clock_gettime(CLOCK_REALTIME, &t1);
        while(bcm2835_gpio_lev(_pin) == HIGH){

        }
        clock_gettime(CLOCK_REALTIME, &t2);
        difference = ((t2.tv_sec * 1000000000L) + t2.tv_nsec)
                   - ((t1.tv_sec * 1000000000L) + t1.tv_nsec);
        timePeekToBottom += difference;

    }
    timePeekToBottom /= AVERAGE_READING; //Durschnittliche Zeit in ns
    timePeekToBottom /= 1000; //ns to ms

    frequenz = 500000 / timePeekToBottom;
    return frequenz; //ms to hz
}

uint8_t HumiditySensor::getPin(){
    return this->_pin;
}

void HumiditySensor::setPin(uint8_t pin){
    this->_pin = pin;
}
