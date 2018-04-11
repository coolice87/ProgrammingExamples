#include<stdio.h>

void add_ints(int * __restrict pa, int * __restrict pb, unsigned int n, int x)
{
	unsigned int i;
	for(i = 0; i < (n & ~3); i++)
		pa[i] = pb[i] + x;
}

void add_floats(float * __restrict pa, float * __restrict pb, unsigned int n, float x)
{
	unsigned int i;
	for(i = 0; i < (n & ~3); i++)
		pa[i] = pb[i] + x;
}

