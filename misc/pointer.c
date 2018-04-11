#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>

struct pointer
{
	uint32_t v1;
	char buf[16];
	uint32_t *pv2;
};

int main(void)
{
	struct pointer *p =NULL;

	printf("buf size:%d, %d\n", sizeof(p->buf), sizeof(*p->buf));
	printf("v1 size:%d, %d\n", sizeof(p->v1), sizeof(p->v1));
	printf("pv2 size:%d, %d\n", sizeof(p->pv2), sizeof(*p->pv2));

	return 0;
}
