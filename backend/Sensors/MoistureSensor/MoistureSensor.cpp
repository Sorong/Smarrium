#include "./MoistureSensor.hpp"

MoistureSensor::MoistureSensor(int intervall, uint8_t channel, int id, ADC* ADC): Sensor(intervall)
{
    this->_id = id;
    this->_channel = channel;
    this->_ADC = ADC;
}

bool MoistureSensor::getEvent(sensors_event_t* event){
    memset(event, 0, sizeof(sensors_event_t));

    event->version   = sizeof(sensors_event_t);
    event->sensor_id = _id;
    event->type      = SENSOR_TYPE_MOISTURE;
    event->timestamp = bcm2835_st_read();
    event->moisture = readMoisture();
    return true;
}

void MoistureSensor::getSensor(sensor_t* sensor){
    /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, "MoistSensor", sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = 1;
  sensor->sensor_id   = _id;
  sensor->type        = SENSOR_TYPE_MOISTURE;
  sensor->min_delay   = 0;
  sensor->max_value   = 17000.0;  /* Based on trial and error ... confirm! */
  sensor->min_value   = 1.0;
  sensor->resolution  = 1.0;
}



float MoistureSensor::readMoisture(){
    return (float)_ADC->myAnalogRead(this->_channel);
}
