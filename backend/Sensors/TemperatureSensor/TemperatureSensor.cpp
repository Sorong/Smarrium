#include "TemperatureSensor.hpp"

bool TemperatureSensor::getEvent(sensors_event_t* event){
    
    memset(event, 0, sizeof(sensors_event_t));

    event->version   = sizeof(sensors_event_t);
    event->sensor_id = _sensorID;
    event->type      = SENSOR_TYPE_TEMPERATURE;
    event->timestamp = bcm2835_st_read();
    event->temperature = readTemperature();

    if (event->temperature == -2000) {
        return false;
    }
    return true;

}

void TemperatureSensor::getSensor(sensor_t *sensor)
{
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, "DS18B20", sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = 1;
  sensor->sensor_id   = _sensorID;
  sensor->type        = SENSOR_TYPE_TEMPERATURE;
  sensor->min_delay   = 0;
  sensor->max_value   = 17000.0;  /* Based on trial and error ... confirm! */
  sensor->min_value   = 1.0;
  sensor->resolution  = 1.0;
}

float TemperatureSensor::readTemperature(){
    //if (presence(_pin) == 1){
    //    return -1000;
    //}
    _wire->writeByte(_pin, SKIP_ROM);
    convert();
    //presence(_pin);
    _wire->writeByte(_pin, SKIP_ROM);
    _wire->writeByte(_pin, READ_SCRATCH);
    uint8_t data[9];
    for (int i = 0; i < 9; i++) {
        data[i] = _wire->readByte(_pin);
    }
    //uint8_t crc = crc8(data, 9);

    //if(crc!=0){
    //    return -2000;
    //}

    int t1 = data[0];
    int t2 = data[1];
    int16_t temp1 = (t2 << 8 | t1);
    float temp = (float) temp1 / 16;
    return temp;
}

void TemperatureSensor::convert(){
    _wire->writeByte(_pin, CONVERT_TEMP);
    for (int i = 0; i < 1000; i++) {
        bcm2835_delayMicroseconds(100000);
        if (_wire->readBit(_pin) == 1){
            break;
        }
    }
}

