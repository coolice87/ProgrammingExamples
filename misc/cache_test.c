#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>

#define ARR_LEN 		5*1024
#define ONE_ARR_LEN 	25*1024*1024
uint32_t arr[ARR_LEN][ARR_LEN] = {0};
uint32_t oarr[ONE_ARR_LEN] = {0};

int main(int argc, char *argv[])
{
	struct timeval t1, t2;
	struct timezone tz;
	uint32_t time1, time2;
	uint32_t i, j;

	printf("size arr:%d, one_arr:%d\n", sizeof(arr), sizeof(oarr));

	//1
	gettimeofday(&t1, &tz);
	time1 = t1.tv_sec*1000 + t1.tv_usec / 1000;
	for(i=0; i<ONE_ARR_LEN; i++)
	{
		oarr[i] *= 3;
	}
	gettimeofday(&t2, &tz);
	time2 = t2.tv_sec*1000 + t2.tv_usec / 1000;
	printf("cost time1: %d ms\n", time2-time1);

	//2
	gettimeofday(&t1, &tz);
	time1 = t1.tv_sec*1000 + t1.tv_usec / 1000;
	for(i=0; i<ARR_LEN; i++)
	{
		for(j=0; j<ARR_LEN; j++)
			arr[i][j] *= 3;
	}
	gettimeofday(&t2, &tz);
	time2 = t2.tv_sec*1000 + t2.tv_usec / 1000;
	printf("cost time2: %d ms\n", time2-time1);

	//3
	gettimeofday(&t1, &tz);
	time1 = t1.tv_sec*1000 + t1.tv_usec / 1000;
	for(i=0; i<ARR_LEN; i++)
	{
		for(j=0; j<ARR_LEN; j++)
			arr[i][j] *= 3;
	}
	gettimeofday(&t2, &tz);
	time2 = t2.tv_sec*1000 + t2.tv_usec / 1000;
	printf("cost time3: %d ms\n", time2-time1);

	//4
	gettimeofday(&t1, &tz);
	time1 = t1.tv_sec*1000 + t1.tv_usec / 1000;
	for(i=0; i<ARR_LEN; i++)
	{
		for(j=0; j<ARR_LEN; j++)
			arr[j][i] *= 3;
	}
	gettimeofday(&t2, &tz);
	time2 = t2.tv_sec*1000 + t2.tv_usec / 1000;
	printf("cost time4: %d ms\n", time2-time1);

}	

