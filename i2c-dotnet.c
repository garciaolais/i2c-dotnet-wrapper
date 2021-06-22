#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

int reg_read_byte(int fd, uint8_t addr, uint8_t regaddr, uint8_t* content) 
{
	struct i2c_rdwr_ioctl_data iocall;    // structure pass to i2c driver
	struct i2c_msg i2c_msgs[2];

	iocall.nmsgs = 2;
	iocall.msgs = i2c_msgs;

	i2c_msgs[0].addr = addr;
	i2c_msgs[0].flags = 0; //write
	i2c_msgs[0].buf = (char*) &regaddr;
	i2c_msgs[0].len = 1;

	i2c_msgs[1].addr = addr;
	i2c_msgs[1].flags = I2C_M_RD; //READ
	i2c_msgs[1].buf = (char*) content;
	i2c_msgs[1].len = 1;

	if (ioctl(fd, I2C_RDWR, (unsigned long) &iocall) < 0) {
		printf("i2c-dotnet:%s:%s \n", __func__, strerror(errno));
		return -1;
	}
	
	return 0;
}

int reg_read_short(int fd, uint8_t addr, uint8_t regaddr, uint16_t* content) 
{
	struct i2c_rdwr_ioctl_data iocall;    // structure pass to i2c driver
	struct i2c_msg i2c_msgs[2];
	uint8_t buffer[2];

	iocall.nmsgs = 2;
	iocall.msgs = i2c_msgs;

	i2c_msgs[0].addr = addr;
	i2c_msgs[0].flags = 0; //write
	i2c_msgs[0].buf = (char*) &regaddr;
	i2c_msgs[0].len = 1;

	i2c_msgs[1].addr = addr;
	i2c_msgs[1].flags = I2C_M_RD; //READ
	i2c_msgs[1].buf = (char*) buffer;
	i2c_msgs[1].len = 2;

	if (ioctl(fd, I2C_RDWR, (unsigned long) &iocall) < 0) {
		printf("%i2c-dotnet:s:%s \n", __func__, strerror(errno));
		return -1;
	}

	*content = (uint16_t) (buffer[0] << 8) | buffer[1];

	return 0;
}

int reg_read_24(int fd, uint8_t addr, uint8_t regaddr, int32_t* content) 
{
	struct i2c_rdwr_ioctl_data iocall;    // structure pass to i2c driver
	struct i2c_msg i2c_msgs[2];
	uint8_t buffer[3];

	iocall.nmsgs = 2;
	iocall.msgs = i2c_msgs;

	i2c_msgs[0].addr = addr;
	i2c_msgs[0].flags = 0; //write
	i2c_msgs[0].buf = (char*) &regaddr;
	i2c_msgs[0].len = 1;

	i2c_msgs[1].addr = addr;
	i2c_msgs[1].flags = I2C_M_RD; //READ
	i2c_msgs[1].buf = (char*) buffer;
	i2c_msgs[1].len = 3;

	if (ioctl(fd, I2C_RDWR, (unsigned long) &iocall) < 0) {
		printf("%i2c-dotnet:s:%s \n", __func__, strerror(errno));
		return -1;
	}

	*content = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];

	return 0;
}

int reg_write_byte(int fd, uint8_t addr, uint8_t regaddr, uint8_t content) 
{
	struct i2c_rdwr_ioctl_data iocall;    // structure pass to i2c driver
	struct i2c_msg i2c_msgs;
	uint8_t buffer[2];

	buffer[0] = regaddr;
	buffer[1] = content;

	iocall.nmsgs = 1;
	iocall.msgs = &i2c_msgs;

	i2c_msgs.addr = addr;
	i2c_msgs.flags = 0; //write
	i2c_msgs.buf = (char*) buffer;
	i2c_msgs.len = sizeof(buffer);
	
	if (ioctl(fd, I2C_RDWR, (unsigned long) &iocall) < 0) {
		printf("i2c-dotnet:%s:%s \n", __func__, strerror(errno));
		return -1;
	}

	return 0;
}

int reg_write_bytes(int fd, uint8_t addr, int16_t *content, int size) 
{
	struct i2c_rdwr_ioctl_data iocall;    // structure pass to i2c driver
	struct i2c_msg i2c_msgs;

	char *buf = malloc( sizeof(char) * size );
	int i = 0;

	for(i = 0 ; i < size; i++){ buf[i] = content[i]; }

	iocall.nmsgs = 1;
	iocall.msgs = &i2c_msgs;
	i2c_msgs.addr = addr;
	i2c_msgs.flags = 0; 
	i2c_msgs.len = size;
	i2c_msgs.buf = buf;

	if (ioctl(fd, I2C_RDWR, (unsigned long) &iocall) < 0) {
		printf("i2c-dotnet:%s:%s \n", __func__, strerror(errno));
		return -1;
	}
	
	free(buf);
	return 0;
}
