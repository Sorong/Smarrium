#include "./UVSensor.hpp"

UVSensor::UVSensor(uint8_t pinUVin, uint8_t pinRef,uint32_t sensorID)
{
    _pinUVin = pinUVin;
    _pinRef = pinRef;
    _sensorID = sensorID;
    pinMode(pinUVin, INPUT);
    pinMode(pinRef, INPUT);

}

UVSensor::~UVSensor()
{

}

float UVSensor::calculateUV()
{
    uint32_t uvLevel = averageAnalogRead(_pinUVin);
    uint32_t refLevel = averageAnalogRead(_pinRef);

    float outputVoltage = 3.3 / refLevel * uvLevel;
    float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0);

    return uvIntensity;

}

float UVSensor::averageAnalogRead(uint8_t pinToRead)
{
  uint8_t numberOfReadings = 8;
  uint32_t runningValue = 0; 

  for(int x = 0 ; x < numberOfReadings ; x++)
  {
      runningValue += analogRead(pinToRead);
  }
    
  runningValue /= numberOfReadings;

  return runningValue;  
}

float UVSensor::mapfloat(float x, float inMin, float inMax, float outMin, float outMax)
{
    return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

bool UVSensor::getEvent(sensors_event_t* event)
{
    /* Clear the event */
    memset(event, 0, sizeof(sensors_event_t));

    event->version   = sizeof(sensors_event_t);
    event->sensor_id = _sensorID;
    event->type      = SENSOR_TYPE_LIGHT;
    event->timestamp = bcm2835_st_read();

    /* Calculate the actual lux value */
    event->uv = calculateUV();

    if (event->uv == 65536) {
        return false;
    }
    return true;
}


void UVSensor::getSensor(sensor_t* sensor){
    memset(sensor, 0, sizeof(sensor_t));

    /* Insert the sensor name in the fixed length char array */
    strncpy (sensor->name, "ML8511", sizeof(sensor->name) - 1);
    sensor->name[sizeof(sensor->name)- 1] = 0;
    sensor->version     = 1;
    sensor->sensor_id   = _sensorID;
    sensor->type        = SENSOR_TYPE_UV;
    sensor->min_delay   = 0;
    sensor->max_value   = 17000.0;  /* Based on trial and error ... confirm! */
    sensor->min_value   = 1.0;
    sensor->resolution  = 1.0;
}

void UVSensor::enableAutoRange(bool enabled){

}