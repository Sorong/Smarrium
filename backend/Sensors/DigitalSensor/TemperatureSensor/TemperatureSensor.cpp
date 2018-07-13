#include "TemperatureSensor.hpp"

TemperatureSensor::TemperatureSensor(int intervall, uint8_t pin, Bcm2835Interface* wire): Sensor(intervall)
{
    this->_pin = pin;
    this->_wire = wire;
}

TemperatureSensor::~TemperatureSensor(){

}

bool TemperatureSensor::getEvent(sensors_event_t* event){
    
    memset(event, 0, sizeof(sensors_event_t));

    event->version   = sizeof(sensors_event_t);
    event->sensor_id = _id;
    event->type      = SENSOR_TYPE_TEMPERATURE;
    event->timestamp = bcm2835_st_read();
    event->temperature = readTemperature();

    if (event->temperature == -2000) {
        return false;
    }
    return true;

}

void TemperatureSensor::getDigitalSensor(sensor_digital_t *sensor)
{

  memset(sensor, 0, sizeof(sensor_digital_t));

  strncpy (sensor->name, "DS18B20", sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = 1;
  sensor->sensor_id   = _id;
  sensor->type        = SENSOR_TYPE_TEMPERATURE;
  sensor->pin         = _pin;
}

void TemperatureSensor::setPin(uint8_t pin){
    this->_pin = pin;
}

uint8_t TemperatureSensor::getPin(){
    return this->_pin;
}

float TemperatureSensor::readTemperature(){
    if (this->_wire->initConversation(_pin) == 1){
       return -1000;
    }
    _wire->writeByte(_pin, SKIP_ROM);
    convert();
    this->_wire->initConversation(_pin);
    _wire->writeByte(_pin, SKIP_ROM);
    _wire->writeByte(_pin, READ_SCRATCH);
    uint8_t data[9];
    for (int i = 0; i < 9; i++) {
        data[i] = _wire->readByte(_pin);
    }

    int t1 = data[0];
    int t2 = data[1];
    int16_t temp1 = (t2 << 8 | t1);
    float temp = (float) temp1 / 16;
    return temp;
}

sensors_type_t TemperatureSensor::getType() const
{
    return SENSOR_TYPE_TEMPERATURE;
}

void TemperatureSensor::convert(){
    _wire->writeByte(_pin, CONVERT_TEMP);
    for (int i = 0; i < 1000; i++) {
        bcm2835_delayMicrosecond(100000);
        if (_wire->readBit(_pin) == 1){
            break;
        }
    }
}

