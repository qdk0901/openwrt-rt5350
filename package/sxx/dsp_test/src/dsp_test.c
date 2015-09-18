#include "libdsp.h"

int main()
{
	unsigned short reg;
	unsigned short dat[3];
	int fd = libspi_init();
	int i;

	for (i = 0x3000; i < 3000 + 0x1000; i++) {
		dat[0] = dat[1] = dat[2] = 0;
		libspi_write(fd, i, dat);	
	}
	
	reg = 0x3004;
	dat[0] = 0x1550;
	dat[1] = 0x781b;
	dat[2] = 0xdb01;
	
	libspi_write(fd, reg, dat);
	libspi_read(fd, reg, dat);
	printf("## %04x %04x %04x %04x\n", reg, dat[0], dat[1], dat[2]);

	reg = 0x3001;
	dat[0] = 0x0000;
	dat[1] = 0x0000;
	dat[2] = 0x0008;
	
	libspi_write(fd, reg, dat);
	libspi_read(fd, reg, dat);
	printf("## %04x %04x %04x %04x\n", reg, dat[0], dat[1], dat[2]);

	int ret = libdsp_init();
	
	printf("dsp init ret: %d\n", ret);
	return 0;
}


