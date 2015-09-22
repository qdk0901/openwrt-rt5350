#include "libdsp.h"

int main()
{
	unsigned short reg;
	unsigned short dat[3];
	int fd = libspi_init();
	int i;

	reg = 0x3003;
	dat[0] = 0x0000;
	dat[1] = 0x0000;
	dat[2] = 0x05fb;
	
	sxx_libspi_write(fd, reg, dat);
	
	reg = 0x3004;
	dat[0] = 0x1550;
	dat[1] = 0x781b;
	dat[2] = 0xdb01;
	
	sxx_libspi_write(fd, reg, dat);
	
	reg = 0x3001;
	dat[0] = 0x0000;
	dat[1] = 0x0000;
	dat[2] = 0x0008;
	
	sxx_libspi_write(fd, reg, dat);
	
	int ret = libdsp_init();
	
	printf("dsp init ret: %d\n", ret);
	return 0;
}


