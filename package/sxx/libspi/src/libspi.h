#ifndef _LIBSPI_H_
#define _LIBSPI_H_

//初始化函数，用来打开spi接口并返回文件句柄
int libspi_init();

//读函数，返回的dat1，dat2，dat3存于参数dat数组中
int libspi_read(int fd, unsigned short reg, unsigned short* dat);

//写函数，请把要写入的dat1, dat2, dat3放到dat数组中
int libspi_write(int fd, unsigned short reg, unsigned short* dat);
#endif