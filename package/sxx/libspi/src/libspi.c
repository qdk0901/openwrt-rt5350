#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>

#include "spidev.h"
#include "libspi.h"

#define DSPIF_PATH	"/dev/spidev32766.1"
#define MAX_SPEED	1000000
#define SPI_MODE	SPI_MODE_3
#define BITS_PER_WORD	16

int libspi_init()
{
	int fd;
	//CPOL = 1, CPHA = 1
	int mode = SPI_MODE;
	// MSB first
	int lsb = 0;
	int bits = BITS_PER_WORD;	
	int speed = MAX_SPEED;

	fd = open(DSPIF_PATH, O_RDWR);
	if (fd < 0) {
		printf("open %s error: %s\n", DSPIF_PATH, strerror(errno));
		return fd;	
	}

	ioctl(fd, SPI_IOC_WR_MODE, &mode);
	ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	ioctl(fd, SPI_IOC_WR_LSB_FIRST, &lsb);
	ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	
	printf("mode: %d\n", mode);
	printf("lsb: %d\n", lsb);
	printf("max speed: %d\n", speed);
	printf("bits per word: %d\n", bits);
	return fd;
}

int libspi_read(int fd, unsigned short reg, unsigned short* dat)
{
	int ret;
	// cmd[16bits] data[16bits] data[16bits] data[16bits]
	dat[0] = dat[1] = dat[2] = 0;

	reg = (reg << 1) | 0x8000;

	struct spi_ioc_transfer t[4] = {
		{
			.tx_buf = &reg,
			.rx_buf = NULL,
			.len = 2,
			.delay_usecs = 2,
			.speed_hz = MAX_SPEED,
			.bits_per_word = BITS_PER_WORD,
			.cs_change = 1,
		},
		{
			.tx_buf = NULL,
			.rx_buf = &dat[0],
			.len = 2,
			.delay_usecs = 2,
			.speed_hz = MAX_SPEED,
			.bits_per_word = BITS_PER_WORD,
			.cs_change = 1,
		},
		{
			.tx_buf = NULL,
			.rx_buf = &dat[1],
			.len = 2,
			.delay_usecs = 2,
			.speed_hz = MAX_SPEED,
			.bits_per_word = BITS_PER_WORD,
			.cs_change = 1,
		}
		,
		{
			.tx_buf = NULL,
			.rx_buf = &dat[2],
			.len = 2,
			.delay_usecs = 2,
			.speed_hz = MAX_SPEED,
			.bits_per_word = BITS_PER_WORD,
			.cs_change = 1,
		},
	};

	

	ret = ioctl(fd, SPI_IOC_MESSAGE(4), t);
	if (ret < 0) {
		printf("spi read failed: %s\n", strerror(errno));
	}

	return ret;
}

int libspi_write(int fd, unsigned short reg, unsigned short* dat)
{
	int ret;
	// cmd[16bits] data[16bits] data[16bits] data[16bits]
	reg = reg << 1;

	struct spi_ioc_transfer t[4] = {
		{
			.tx_buf = &reg,
			.rx_buf = NULL,
			.len = 2,
			.delay_usecs = 2,
			.speed_hz = MAX_SPEED,
			.bits_per_word = BITS_PER_WORD,
			.cs_change = 1,
		},
		{
			.tx_buf = &dat[0],
			.rx_buf = NULL,
			.len = 2,
			.delay_usecs = 2,
			.speed_hz = MAX_SPEED,
			.bits_per_word = BITS_PER_WORD,
			.cs_change = 1,
		},
		{
			.tx_buf = &dat[1],
			.rx_buf = NULL,
			.len = 2,
			.delay_usecs = 2,
			.speed_hz = MAX_SPEED,
			.bits_per_word = BITS_PER_WORD,
			.cs_change = 1,
		}
		,
		{
			.tx_buf = &dat[2],
			.rx_buf = NULL,
			.len = 2,
			.delay_usecs = 2,
			.speed_hz = MAX_SPEED,
			.bits_per_word = BITS_PER_WORD,
			.cs_change = 1,
		},
	};

	ret = ioctl(fd, SPI_IOC_MESSAGE(4), t);
	if (ret < 0) {
		printf("spi read failed: %s\n", strerror(errno));
	}
	return ret;
}


