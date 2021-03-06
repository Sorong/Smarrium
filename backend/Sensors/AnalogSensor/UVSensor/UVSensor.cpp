#include "./UVSensor.hpp"
#include <QDebug>
UVSensor::UVSensor(int intervall, uint8_t channel, ADC* adc): Sensor(intervall)
{
    _channel = channel;
    _adc = adc;
    this->name = "UV-Sensor, Kanal: " + QString::number(this->_channel + 1);

}

UVSensor::~UVSensor()
{

}

float UVSensor::calculateUV()
{
    float refLevel = averageAnalogRead(_channel);

    float voltOutput = refLevel * (3.3 / 1023.0);
    qDebug() << voltOutput;
    voltOutput = voltOutput / 4.3;
    float uvIntensity = voltOutput * 9.0;
    return uvIntensity;

}

sensors_type_t UVSensor::getType() const
{
    return SENSOR_TYPE_UV;
}

QString UVSensor::getSort(){
    return this->sort;
}

SensorBaseType UVSensor::getRawType()
{
    return SensorBaseType::UV;
}

float UVSensor::averageAnalogRead(uint8_t pinToRead)
{
  uint8_t numberOfReadings = 8;
  uint32_t runningValue = 0; 

  for(int x = 0 ; x < numberOfReadings ; x++)
  {
      runningValue += _adc->myAnalogRead(pinToRead);
  }
    
  runningValue /= numberOfReadings;

  return runningValue;  
}


bool UVSensor::getEvent(sensors_event_t* event)
{
    /* Clear the event */
    memset(event, 0, sizeof(sensors_event_t));

    event->version   = sizeof(sensors_event_t);
    event->sensor_id = _id;
    event->type      = SENSOR_TYPE_UV;
    event->timestamp = QTime::currentTime();

    /* Calculate the actual lux value */
    event->uv = calculateUV();

    if (event->uv == 65536) {
        return false;
    }
    return true;
}


void UVSensor::getAnalogSensor(sensor_analog_t *sensor){
    memset(sensor, 0, sizeof(sensor_analog_t));

    strncpy (sensor->name, "ML8511", sizeof(sensor->name) - 1);
    sensor->name[sizeof(sensor->name)- 1] = 0;
    sensor->version     = 1;
    sensor->sensor_id   = _id;
    sensor->type        = SENSOR_TYPE_UV;
    sensor->channel     = _channel;
}

void UVSensor::setChannel(uint8_t channel){
    this->_channel = channel;
}

uint8_t UVSensor::getChannel(){
    return this->_channel;
}
