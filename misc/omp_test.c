#include<stdio.h>
#include<stdlib.h>
#include <sys/time.h>

int main(void)
{
	int i,j;
	int sec;
	struct timeval t1, t2;

	gettimeofday(&t1, NULL);
	//#pragma omp parallel
	{
		for (i=0;i<10000;i++)
		{
			for(j=0; j<100000; j++)
				;
		}
	}
	gettimeofday(&t2, NULL);

	sec = t2.tv_sec*1000 + t2.tv_usec/1000 -  (t1.tv_sec*1000 + t1.tv_usec/1000);
	printf("sec:%d\n", sec);

	return 0;
}
