#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <errno.h>

int read_byte_data(int fd, uint8_t addr, uint8_t regaddr)
{
        uint8_t* content; 
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
		printf("error during reg_read_byte()\n");
		return -1;
	}
	return *content;
}

int reg_read_byte(int fd, uint8_t addr, uint8_t regaddr,
		uint8_t* content) {
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
		printf("error during reg_read_byte()\n");
		return -1;
	}
	return 0;
}

int write_byte_data(int fd, uint8_t addr, uint8_t cmd, uint8_t val) {
	struct i2c_rdwr_ioctl_data iocall;    // structure pass to i2c driver
	struct i2c_msg i2c_msgs;
	uint8_t data[2];

	data[0] = cmd;
	data[1] = val;

	iocall.nmsgs = 1;
	iocall.msgs = &i2c_msgs;

	i2c_msgs.addr = addr;
	i2c_msgs.flags = 0; 
	i2c_msgs.buf = (char*) data;
	i2c_msgs.len = sizeof(data);

	if (ioctl(fd, I2C_RDWR, (unsigned long) &iocall) < 0) {
		printf("%s: error\n", __func__);
		return -1;
	}
	return 0;
}

int reg_write_byte(int fd, uint8_t addr, uint8_t regaddr,
		uint8_t content) {
	struct i2c_rdwr_ioctl_data iocall;    // structure pass to i2c driver
	struct i2c_msg message;
	uint8_t buffer[2];

	buffer[0] = regaddr;
	buffer[1] = content;

	iocall.nmsgs = 1;
	iocall.msgs = &message;
	message.addr = addr;
	message.flags = 0; //write
	message.buf = (char*) buffer;
	message.len = sizeof(buffer);
	if (ioctl(fd, I2C_RDWR, (unsigned long) &iocall) < 0) {
		printf("%s:%s \n", __func__, strerror(errno));
		return -1;
	}
	return 0;
}

int reg_read_byte_(int fd, uint8_t addr, uint8_t regaddr,
		uint8_t* content) {
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
	i2c_msgs[1].len = 2;

	if (ioctl(fd, I2C_RDWR, (unsigned long) &iocall) < 0) {
		printf("%s:%s \n", __func__, strerror(errno));
		return -1;
	}
	return 0;
}

int reg_read_short(int fd, uint8_t addr, uint8_t regaddr,
		uint16_t* content) {
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
		printf("%s:%s \n", __func__, strerror(errno));
		return -1;
	}

	*content = (uint16_t) (buffer[0] << 8) | buffer[1];
	return 0;
}

int reg_read_24(int fd, uint8_t addr, uint8_t regaddr, int32_t* content) {
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
		printf("%s:%s \n", __func__, strerror(errno));
		return -1;
	}

	*content = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];
	return 0;
}
