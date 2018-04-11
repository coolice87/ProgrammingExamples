#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <execinfo.h>

/********* test.c *********/

#if 0
void *mine_memcpy(void *  s1, const void * s2, register size_t n)
{
	register char *r1 = (char *)s1;
	register const char *r2 = (char *)s2;

	while (n) {
		*r1++ = *r2++;
		--n;
	}

	return s1;
}
#endif

#if 1
void *__wrap_memcpy(void *dst, void *src, size_t n) 
{ 
	printf("%s\n", __func__);
	if(NULL == dst || NULL==src)
		return NULL;

	if((dst == src)
		|| ((dst<src) && ((char *)src<= (char*)dst+n))
		|| ((src<dst) && ((char *)dst<=(char *)src +n))
		)
	{
		printf("memery is overlapping\n");
		return NULL;
	}
	printf("dst:%#x, src:%#x\n", dst, src);
	return __real_memcpy(dst, src, n);
//	return mine_memcpy(dst, src, n);
}
#endif

#if 0
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

void dump_stack(void)
{
	void *array[16];
	size_t size = backtrace(array, ARRAY_SIZE(array));
	char **strings = backtrace_symbols(array, size);
	size_t i;

	printf("Obtained %zd stack frames.\n", size);

	for (i = 0; i < size; i++)
		printf("%s\n", strings[i]);

	free(strings);
}
#endif
int main(int argc, char *argv[])
{
	char *src= "123456790";
	char dst[16];
	const int i = 1;
	int *p = &i;

	*p = 10;

	printf("i:%d\n", i);

	memcpy(dst, src, strlen(src));
	printf("%s\n", dst);
	//dump_stack();

	//sleep(1);

	return 0;
}
