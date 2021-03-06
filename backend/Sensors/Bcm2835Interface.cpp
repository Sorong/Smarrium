#include "Bcm2835Interface.hpp"

Bcm2835Interface::Bcm2835Interface(){
    qDebug() << "bcm2835_init";
    if (!bcm2835_init())
    {
        qDebug() << "bcm2835_init failed. Are you running as root??\n";
    }
}

uint8_t Bcm2835Interface::read8(uint8_t address, uint8_t reg){
    char data[2];
    memset(data, 0, sizeof(char));
    bcm2835_i2c_begin();
    data[0] = reg;


    bcm2835_i2c_set_baudrate(2500);
    bcm2835_i2c_setSlaveAddress(address);
            
	int err = bcm2835_i2c_write(data, 1);
	if( err != BCM2835_I2C_REASON_OK ) {

        //printf("Read8: Unable to write command register %02x\n",err);
		return 0;
	}
	err = bcm2835_i2c_read(data, 1);
	if( err != BCM2835_I2C_REASON_OK ) {
        //printf("Read8: Unable to read last command response %02x\n",err);
		return 0;
	}

    bcm2835_i2c_end();
	return data[0];

}

uint16_t Bcm2835Interface::read16(uint8_t address, uint8_t reg){
    char data[2];
    memset(data, 0, sizeof(char) * 2);
    uint16_t readValue = 0;
    data[0] = reg;
    bcm2835_i2c_begin();
    bcm2835_i2c_set_baudrate(25000);
    bcm2835_i2c_setSlaveAddress(address);
            
	int err = bcm2835_i2c_write(data, 1);
	if( err != BCM2835_I2C_REASON_OK ) {
		printf("Read16: Unable to write command register %02x\n",err);
		return 0;
	}
	err = bcm2835_i2c_read(data, 2);
	if( err != BCM2835_I2C_REASON_OK ) {
		printf("Read16: Unable to read last command response %02x\n",err);
		return 0;
	}

    bcm2835_i2c_end();
    readValue = (((data[1]) << 8) + data[0]);

	return readValue;
}

uint16_t Bcm2835Interface::read16repeatedStart(uint8_t address, uint8_t reg){
    char data[2];
    memset(data, 0, sizeof(char) * 2);
    uint16_t readValue = 0;
    data[0] = reg;
    bcm2835_i2c_begin();
    bcm2835_i2c_set_baudrate(25000);
    bcm2835_i2c_setSlaveAddress(address);
            
	int err = bcm2835_i2c_write(data, 1);
	if( err != BCM2835_I2C_REASON_OK ) {
		printf("Read16R: Unable to write command register %02x\n",err);
		return 0;
	}
	err = bcm2835_i2c_read_register_rs(data, data, 2);
	if( err != BCM2835_I2C_REASON_OK ) {
		printf("Read16R: Unable to read last command response %02x\n",err);
		return 0;
	}

    bcm2835_i2c_end();
    readValue = (((data[1]) << 8) + data[0]);

	return readValue;
}

void Bcm2835Interface::write8(uint8_t address, uint8_t reg, uint8_t value){
    char data[1];
    memset(data, 0, sizeof(char));
    bcm2835_i2c_begin();
    bcm2835_i2c_set_baudrate(25000);
    bcm2835_i2c_setSlaveAddress(address);

    data[0] = reg;
	int err = bcm2835_i2c_write(data,1);
	if( err != BCM2835_I2C_REASON_OK ) {
		printf("Write8: Unable to write command register %02x\n",err);
		return;
	}
	
    data[0] = value;
	err = bcm2835_i2c_write(data,1);
	if( err != BCM2835_I2C_REASON_OK ) {
		printf("Write8: Unable to write command register %02x\n",err);
		return;
	}

    bcm2835_i2c_end();
	return;
}

void Bcm2835Interface::write16repeatedStart(uint8_t address, uint8_t reg, uint16_t value){
    char data[4];
    char lsb = value & 0x00FF;
    char msb = (value >> 8);
    char crc = crc8(0, (address << 1));
	crc = crc8(crc, reg);
	crc = crc8(crc, lsb);
	crc = crc8(crc, msb);

    bcm2835_i2c_begin();
    bcm2835_i2c_set_baudrate(25000);
    bcm2835_i2c_setSlaveAddress(address);

    data[0] = reg;
    data[1] = lsb;
    data[2] = msb;
    data[3] = crc;

    bcm2835_i2c_write_read_rs(data, 4, data, 4);
    bcm2835_i2c_end();
	return;
}

void Bcm2835Interface::write16(uint8_t address, uint8_t reg, uint16_t value){
    char data[1];
    memset(data, 0, sizeof(char));
    bcm2835_i2c_begin();
    bcm2835_i2c_set_baudrate(25000);
    bcm2835_i2c_setSlaveAddress(address);

    data[0] = reg;
	int err = bcm2835_i2c_write(data,1);
	if( err != BCM2835_I2C_REASON_OK ) {
		printf("Write16: Unable to write command register %02x\n",err);
		return;
	}
	
    memset(data, value, sizeof(char) * 2);
	err = bcm2835_i2c_write(data,2);
	if( err != BCM2835_I2C_REASON_OK ) {
		printf("Write16: Unable to write command register %02x\n",err);
		return;
	}

    bcm2835_i2c_end();
	return;
}

uint8_t Bcm2835Interface::readBit(uint8_t pin) {
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(pin, LOW);
    bcm2835_delayMicrosecond(6);
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
    bcm2835_delayMicrosecond(8);
    uint8_t b = bcm2835_gpio_lev(pin);
    bcm2835_delayMicrosecond(55);
    return b;
}

uint8_t Bcm2835Interface::readByte(uint8_t pin) {
    uint8_t byte = 0;
    int i;
    for (i = 0; i < 8; i++) {
        byte = byte | readBit(pin) << i;
    };
    return byte;
}


void Bcm2835Interface::writeBit(uint8_t pin, int b) {  
    int delay1, delay2;
    if (b == 1) {
        delay1 = 6;
        delay2 = 64;
    } else {
        delay1 = 80;
        delay2 = 10;
    }
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(pin, LOW);
    bcm2835_delayMicrosecond(delay1);
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
    bcm2835_delayMicrosecond(delay2);
}

void Bcm2835Interface::writeByte(uint8_t pin, uint8_t byte) {
    int i;
    for (i = 0; i < 8; i++) {
        if (byte & 1) {
            writeBit(pin,1);
        } else {
            writeBit(pin,0);
        }
        byte = byte >> 1;
    }
}

uint8_t Bcm2835Interface::initConversation(uint8_t pin){
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(pin, LOW);
    bcm2835_delayMicrosecond(480);
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
    bcm2835_delayMicrosecond(70);
    uint8_t b = bcm2835_gpio_lev(pin);
    bcm2835_delayMicrosecond(410);
    return b;
}
