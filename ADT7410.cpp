#include "ADT7410.h"

ADT7410::ADT7410(uint8_t addr, unsigned char bus){
	_addr = addr;
	_bus = bus;
	_initialized = false;
	setResolution(ADT7410_RESOLUTION_13);
	setMode(ADT7410_NORMAL_MODE);
}

ADT7410::~ADT7410(void){
	close(this->_fd);
}

bool ADT7410::begin(void){
	_initialized = true;
	
	char i2c_dev_fn[64];

	sprintf(i2c_dev_fn, "/dev/i2c-%d",_bus);

	if ((this->_fd = open(i2c_dev_fn, O_RDWR)) < 0) {
                printf("Faild to open i2c port\n");
                return false;
	}

	if(ioctl(this->_fd, I2C_SLAVE, _addr)<0){
                printf("Faild to open i2c port\n");
                return false;
	}

	return true;
}

void ADT7410::setResolution(adt7410Resolution_t resolution){
	_resolution=resolution;

	write8(ADT7410_RESISTER_CONFIGURATION, _resolution | _mode);
}

void ADT7410::setMode(adt7410Mode_t mode){
	_mode=mode;
	
	write8(ADT7410_RESISTER_CONFIGURATION, _resolution | _mode);
}

double ADT7410::calculateTmp(uint16_t code){
	double tmp;

	switch(_resolution){
		case(ADT7410_RESOLUTION_13):
			code >>= 3;
			code =(int)code;
			if(code & 0x1000){
				code-=8192;
			}
			tmp = (double)code/16.0;
			break;
		case(ADT7410_RESOLUTION_16):
			code =(int)code;
			if(code & 0x8000){
				code-=65536;
			}
			tmp = (double)code/128.0;
			break;
	}
	return tmp;
}

uint16_t ADT7410::getTmp(void){
	if(!_initialized) begin();

	usleep(240000);

	uint16_t x;
	x = read8(ADT7410_RESISTER_TEMPERATURE_VALUE_MSB);
	x <<=8;
	x |= read8(ADT7410_RESISTER_TEMPERATURE_VALUE_MSB);

	return x;
} 

uint8_t ADT7410::read8(uint8_t reg)
{
  uint8_t x;

	write(this->_fd,&reg,1);
	read(this->_fd,&x,1);

  return x;
}

void ADT7410::write8 (uint8_t reg, uint8_t value)
{
 	write(this->_fd, &reg, 1);
	write(this->_fd, &value, 1);
}
