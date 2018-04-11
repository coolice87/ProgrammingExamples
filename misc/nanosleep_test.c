#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

int main(void)
{
	struct timeval start, end;
	struct timespec req;

	gettimeofday(&start, NULL);

	req.tv_sec = 0;
	req.tv_nsec = 100000;
	nanosleep(&req, NULL);
	gettimeofday(&end, NULL);

	printf("sec:%d, usec:%d\n", end.tv_sec-start.tv_sec, end.tv_usec-start.tv_usec);	

}

