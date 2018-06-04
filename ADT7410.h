#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
	
#define ADT7410_ADDR_00 0x48
#define ADT7410_ADDR_01 0x49
#define ADT7410_ADDR_10 0x4A
#define ADT7410_ADDR_11 0x4B

typedef enum{
	ADT7410_RESOLUTION_13=(0x00),
	ADT7410_RESOLUTION_16=(0x80)
}adt7410Resolution_t;

typedef enum{
	ADT7410_NORMAL_MODE=(0x00),
	ADT7410_ONE_SHOT_MODE=(0x20),
	ADT7410_ONE_SPS_MODE=(0x40),
	ADT7410_SHUTDOWN_MODE=(0x60)
}adt7410Mode_t;

enum{
//MSB=Most Significant Byte
//LSB=Least Significant Byte
  ADT7410_RESISTER_TEMPERATURE_VALUE_MSB	= 0x00,
  ADT7410_RESISTER_TEMPERATURE_VALUE_LSB	= 0x01,
  ADT7410_RESISTER_STATUS			= 0x02,
  ADT7410_RESISTER_CONFIGURATION		= 0x03,
  ADT7410_RESISTER_THIGH_SETPOINT_MSB	= 0x04,
  ADT7410_RESISTER_THIGH_SETPOINT_LSB	= 0x05,
  ADT7410_RESISTER_TLOW_SETPOINT_MSB	= 0x06,
  ADT7410_RESISTER_TLOW_SETPOINT_LSB	= 0x07,
  ADT7410_RESISTER_TCRIT_SETPOINT_MSB	= 0x08,
  ADT7410_RESISTER_TCRIT_SETPOINT_LSB	= 0x09,
  ADT7410_RESISTER_THYST_SETPOINT		= 0x0A,
  ADT7410_RESISTER_ID			= 0x0B
};

class ADT7410{
	public:
	ADT7410(uint8_t addr, unsigned char bus);
	~ADT7410(void);
	bool begin(void);
	double calculateTmp(uint16_t code);
	void write8 (uint8_t reg, uint8_t value);
	uint8_t read8(uint8_t reg);

	void setResolution(adt7410Resolution_t resolution);
	void setMode(adt7410Mode_t mode);
	uint16_t getTmp(void);

	private:
	int _fd;
	adt7410Resolution_t _resolution;
	adt7410Mode_t _mode;
	int8_t _addr;
	unsigned char _bus;

	bool _initialized;
};
