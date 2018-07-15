#include "InfraredTemperatureSensor.hpp"

IRTemperatureSensor::IRTemperatureSensor(int intervall, uint8_t address, Bcm2835Interface* wire) : Sensor(intervall)
{
	// Set initial values for all private member variables
    this->_address = address;
	_defaultUnit = TEMP_C;
	_rawObject = 0;
	_rawAmbient = 0;
	_rawObject2 = 0;
	_rawMax = 0;
	_rawMin = 0;
    this->name = "Infrarottermometer";
}

void IRTemperatureSensor::enableAutoRange(bool enable){
	return;
}

QString IRTemperatureSensor::getSort(){
    return this->sort;
}


bool IRTemperatureSensor::getEvent(sensors_event_t* event){
	readObject();
	memset(event, 0, sizeof(sensors_event_t));

	event->version   = sizeof(sensors_event_t);
	event->sensor_id = _id;
	event->type      = SENSOR_TYPE_IRTEMPERATURE;
	event->timestamp = bcm2835_st_read();
	
	event->irTemperature = object();

	return true;
}

void IRTemperatureSensor::getI2CSensor(sensor_I2C_t* sensor){
	/* Clear the sensor_t object */
    memset(sensor, 0, sizeof(sensor_I2C_t));

	/* Insert the sensor name in the fixed length char array */
	strncpy (sensor->name, "MLX90614", sizeof(sensor->name) - 1);
	sensor->name[sizeof(sensor->name)- 1] = 0;
	sensor->version     = 1;
	sensor->sensor_id   = _id;
	sensor->type        = SENSOR_TYPE_IRTEMPERATURE;
    sensor->address      = _address;
}


uint8_t IRTemperatureSensor::read()
{
	// read both the object and ambient temperature values
	if (readObject() && readAmbient())
	{
		// If the reads succeeded, return success
		return 1;
	}
	return 0; // Else return fail
}

uint8_t IRTemperatureSensor::readRange()
{
	// Read both minimum and maximum values from EEPROM
	if (readMin() && readMax())
	{
		// If the read succeeded, return success
		return 1;
	}
	return 0; // Else return fail
}

float IRTemperatureSensor::ambient(void)
{
	// Return the calculated ambient temperature
	return calcTemperature(_rawAmbient);
}

float IRTemperatureSensor::object(void)
{
	// Return the calculated object temperature
	return calcTemperature(_rawObject);
}

float IRTemperatureSensor::minimum(void)
{
	// Return the calculated minimum temperature
	return calcTemperature(_rawMin);
}

float IRTemperatureSensor::maximum(void)
{
	// Return the calculated maximum temperature
	return calcTemperature(_rawMax);
}

uint8_t IRTemperatureSensor::readObject()
{
	int16_t rawObj;
	//rawObj = this->_wire->read16(_deviceAddress, MLX90614_REGISTER_TOBJ1);
	// Read from the TOBJ1 register, store into the rawObj variable
	rawObj = I2CReadWord(MLX90614_REGISTER_TOBJ1);
	if (rawObj)
	{
		// If the read succeeded
		if (rawObj & 0x8000) // If there was a flag error
		{
			return 0; // Return fail
		}
		// Store the object temperature into the class variable
		_rawObject = rawObj;
		return 1;
	}
	return 0;	
}

uint8_t IRTemperatureSensor::readObject2()
{
	int16_t rawObj;
	// Read from the TOBJ2 register, store into the rawObj variable
	rawObj = I2CReadWord(MLX90614_REGISTER_TOBJ1);
	if (rawObj)
	{
		// If the read succeeded
		if (rawObj & 0x8000) // If there was a flag error
		{
			return 0; // Return fail
		}
		// Store the object2 temperature into the class variable
		_rawObject2 = rawObj;
		return 1;
	}
	return 0;	
}

uint8_t IRTemperatureSensor::readAmbient()
{
	int16_t rawAmb;

	rawAmb = I2CReadWord(MLX90614_REGISTER_TA);
	// Read from the TA register, store value in rawAmb
	if (rawAmb)
	{
		// If the read succeeds, store the read value
		_rawAmbient = rawAmb; // return success
		return 1;
	}
	return 0; // else return fail
}

uint8_t IRTemperatureSensor::readMax()
{
	int16_t toMax;
	// Read from the TOMax EEPROM address, store value in toMax
	toMax = I2CReadWord(MLX90614_REGISTER_TOMAX);
	if (toMax)
	{
		_rawMax = toMax;
		return 1;
	}
	return 0;
}

uint8_t IRTemperatureSensor::readMin()
{
	int16_t toMin;
	// Read from the TOMin EEPROM address, store value in toMax
	toMin = I2CReadWord(MLX90614_REGISTER_TOMIN);

	if (toMin)
	{
		_rawMin = toMin;
		return 1;
	}
	return 0;
}

uint8_t IRTemperatureSensor::setMax(float maxTemp)
{
	// Convert the unit-ed value to a raw ADC value:
	int16_t rawMax = calcRawTemp(maxTemp);
	// Write that value to the TOMAX EEPROM address:
	return writeEEPROM(MLX90614_REGISTER_TOMAX, rawMax);
}

uint8_t IRTemperatureSensor::setMin(float minTemp)
{
	// Convert the unit-ed value to a raw ADC value:
	int16_t rawMin = calcRawTemp(minTemp);
	// Write that value to the TOMIN EEPROM address:	
    return writeEEPROM(MLX90614_REGISTER_TOMIN, rawMin);
}

sensors_type_t IRTemperatureSensor::getType() const
{
    return SENSOR_TYPE_IRTEMPERATURE;
}

SensorBaseType IRTemperatureSensor::getRawType()
{
    return SensorBaseType::TEMPERATURE;
}

uint8_t IRTemperatureSensor::setEmissivity(float emis)
{
	// Make sure emissivity is between 0.1 and 1.0
	if ((emis > 1.0) || (emis < 0.1))
		return 0; // Return fail if not
	// Calculate the raw 16-bit value:
	uint16_t ke = uint16_t(65535.0 * emis);
	//ke = constrain(ke, 0x2000, 0xFFFF);
	if(ke < 0x2000){
		ke = 0x2000;
	}
	else if(ke > 0xFFFF){
		ke = 0xFFFF;
	}
	// Write that value to the ke register
	return writeEEPROM(MLX90614_REGISTER_KE, (int16_t)ke);
}

float IRTemperatureSensor::readEmissivity(void)
{
	int16_t ke;

	ke = I2CReadWord(MLX90614_REGISTER_KE);
	if (ke)
	{
		// If we successfully read from the ke register
		// calculate the emissivity between 0.1 and 1.0:
		return (((float)((uint16_t)ke)) / 65535.0);
	}
	return 0; // Else return fail
}

uint8_t IRTemperatureSensor::getAddress(void)
{
	int16_t tempAdd;
	// Read from the 7-bit I2C address EEPROM storage address:
	tempAdd = I2CReadWord(MLX90614_REGISTER_ADDRESS);
	if (tempAdd)
	{
		// If read succeeded, return the address:
		return (uint8_t) tempAdd;
	}
	return 0; // Else return fail
}

void IRTemperatureSensor::setAddress(uint8_t newAdd)
{
	int16_t tempAdd;
	// Make sure the address is within the proper range:
	if ((newAdd >= 0x80) || (newAdd == 0x00))
        return; // Return fail if out of range
	// Read from the I2C address address first:
	tempAdd = I2CReadWord(MLX90614_REGISTER_ADDRESS);
	
	if (tempAdd)
	{
		tempAdd &= 0xFF00; // Mask out the address (MSB is junk?)
		tempAdd |= newAdd; // Add the new address
		
         writeEEPROM(MLX90614_REGISTER_ADDRESS, newAdd);
	}	
}

uint8_t IRTemperatureSensor::readID(void)
{	
	for (int i=0; i<4; i++)
	{
		int16_t temp = 0;
		// Read from all four ID registers, beginning at the first:
		temp = I2CReadWord(MLX90614_REGISTER_ID0 + i);
		if (!temp)
			return 0;
		// If the read succeeded, store the ID into the id array:
		id[i] = (uint16_t)temp;
	}
	return 1;
}

uint32_t IRTemperatureSensor::getIDH(void)
{
	// Return the upper 32 bits of the ID
	return ((uint32_t)id[3] << 16) | id[2];
}

uint32_t IRTemperatureSensor::getIDL(void)
{
	// Return the lower 32 bits of the ID
	return ((uint32_t)id[1] << 16) | id[0];
}


int16_t IRTemperatureSensor::calcRawTemp(float calcTemp)
{
	int16_t rawTemp; // Value to eventually be returned
	
	if (_defaultUnit == TEMP_RAW)
	{
		// If unit is set to raw, just return that:
		rawTemp = (int16_t) calcTemp;
	}
	else
	{
		float tempFloat;
		// First convert each temperature to Kelvin:
		if (_defaultUnit == TEMP_F)
		{
			// Convert from farenheit to Kelvin
			tempFloat = (calcTemp - 32.0) * 5.0 / 9.0 + 273.15;
		}
		else if (_defaultUnit == TEMP_C)
		{
			tempFloat = calcTemp + 273.15;
		}
		else if (_defaultUnit == TEMP_K)
		{
			tempFloat = calcTemp;
		}
		// Then multiply by 0.02 degK / bit
		tempFloat *= 50;
		rawTemp = (int16_t) tempFloat;
	}
	return rawTemp;
}

float IRTemperatureSensor::calcTemperature(int16_t rawTemp)
{
	float retTemp;
	
	if (_defaultUnit == TEMP_RAW)
	{
		retTemp = (float) rawTemp;
	}
	else
	{
		retTemp = float(rawTemp) * 0.02;
		if (_defaultUnit != TEMP_K)
		{
			retTemp -= 273.15;
			if (_defaultUnit == TEMP_F)
			{
				retTemp = retTemp * 9.0 / 5.0 + 32;
			}
		}
	}
	
	return retTemp;
}

uint16_t IRTemperatureSensor::I2CReadWord(uint8_t reg){
    return this->_wire->read16repeatedStart(_address, reg);
}

uint8_t IRTemperatureSensor::writeEEPROM(uint8_t reg, int16_t data)
{	
	// Clear out EEPROM first:
	//if (this->_wire->write16(_deviceAddress, 0, reg) != 0)
		//return 0; // If the write failed, return 0
    this->_wire->write16repeatedStart(_address, reg, 0);
	delay(5); // Delay tErase
	
	//uint8_t i2cRet = this->_wire->write16(_deviceAddress, data, reg);
    this->_wire->write16repeatedStart(_address, reg, data);
	delay(5); // Delay tWrite
	return 0;
	// if (i2cRet == 0)
	// 	return 1;
	// else
	// 	return 0;	
}

// uint8_t IRTemperatureSensor::I2CWriteWord(byte reg, int16_t data)
// {
// 	uint8_t crc;
// 	uint8_t lsb = data & 0x00FF;
// 	uint8_t msb = (data >> 8);
	
// 	crc = crc8(0, (_deviceAddress << 1));
// 	crc = crc8(crc, reg);
// 	crc = crc8(crc, lsb);
// 	crc = crc8(crc, msb);
	
// 	Wire.beginTransmission(_deviceAddress);
// 	Wire.write(reg);
// 	Wire.write(lsb);
// 	Wire.write(msb);
// 	Wire.write(crc);
// 	return Wire.endTransmission(true);
// }

uint8_t IRTemperatureSensor::crc8 (uint8_t inCrc, uint8_t inData)
{
	uint8_t i;
	uint8_t data;
	data = inCrc ^ inData;
	for ( i = 0; i < 8; i++ )
	{
		if (( data & 0x80 ) != 0 )
		{
			data <<= 1;
			data ^= 0x07;
		}
		else
		{
			data <<= 1;
		}
	}
	return data;
}

//uint8_t IRTemperatureSensor::I2CReadWord(byte reg, int16_t * dest)
// {
// 	int timeout = I2C_READ_TIMEOUT;
	
// 	Wire.beginTransmission(_deviceAddress);
// 	Wire.write(reg);
	
// 	Wire.endTransmission(false); // Send restart
// 	Wire.requestFrom(_deviceAddress, (uint8_t) 3);
	
// 	while ((Wire.available() < 3) && (timeout-- > 0))
// 		delay(1);
// 	if (timeout <= 0)
// 		return 0;
	
// 	uint8_t lsb = Wire.read();
// 	uint8_t msb = Wire.read();
// 	uint8_t pec = Wire.read();
	
// 	uint8_t crc = crc8(0, (_deviceAddress << 1));
// 	crc = crc8(crc, reg);
// 	crc = crc8(crc, (_deviceAddress << 1) + 1);
// 	crc = crc8(crc, lsb);
// 	crc = crc8(crc, msb);
	
// 	if (crc == pec)
// 	{
// 		*dest = (msb << 8) | lsb;
// 		return 1;
// 	}
// 	else
// 	{
// 		return 0;
// 	}
// }
