#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char*argv[])
{
	float sum = 0;
	float basic = 0;
	float rate = 0;
	char *endptr;
	int year;
	int i;

	if(argc < 4)
	{
		printf("usage: \n");
		printf("./rate basic rate years\n");
		return -1;
	}

	basic = strtod(argv[1], &endptr);
	rate = strtod(argv[2], &endptr)/100.0;
	year = strtol(argv[3], &endptr, 10);
	printf("basic:%0.2f, rate:%0.2f, year:%d\n", basic, rate, year);
	sum = 1;
	for(i=0; i<year; i++)
		sum *= (1+rate);

	sum = sum * basic;

	printf("profile: %0.2f\n", sum);


	return 0;
}
