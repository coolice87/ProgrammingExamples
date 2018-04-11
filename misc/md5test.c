/************************************************************
 * Copyright (C), 2017, Leon, All Rights Reserved.
 * FileName: startdin1.c
 * Description: 启动din1程序,同时监控日志重定向
 * Date: 2017-3-3
 *  ************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define MD5_USRPASSWD_FILE 		"usrpasswd"

//        10 32 0e 1f 21 30 c5 f6 49 3e 4c b1 41 7e 3b 81
//dddin1: 10 32 0e 1f 21 30 c5 f6 49 3e 4c b1 41 7e 3b 81
const uint8_t buf[20] = {0x0f, 0x0f, 0x0f, 0x0f, 0x10, 0x32, 0x0e, 0x1f, 0x21, 0x30, 0xc5, 0xf6, 0x49, 0x3e, 0x4c, 0xb1, 0x41, 0x7e, 0x3b, 0x81};
uint8_t outbuf[64];

int main(int argc, char *argv[])
{
	int fd = -1;
	int i;

	fd = open(MD5_USRPASSWD_FILE, O_RDWR | O_CREAT | O_TRUNC, 00600);
	if(fd < 0){
		perror("open failed\n");
		return -1;
	}

	write(fd, buf, sizeof(buf));
	printf("write: ");
	for(i=0; i<sizeof(buf); i++)
		printf("%02x", buf[i]);
	printf("\n");

	close(fd);
	fd = -1;

	fd = open(MD5_USRPASSWD_FILE, O_RDONLY, 00600);
	if(fd < 0){
		perror("open failed\n");
		return -1;
	}
	
	lseek(fd, 0, SEEK_SET);
	read(fd, outbuf, sizeof(buf));
	printf("read: ");
	for(i=0; i<sizeof(buf); i++)
		printf("%02x", outbuf[i]);
	printf("\n");

	close(fd);

	return 0;

}

