#include <stdlib.h>  
#include <malloc.h>  
#include <string.h>  
  
void test()  
{  
	int *ptr = malloc(sizeof(int)*10);  
	char buf[5];

	ptr = malloc(sizeof(int) * 10);
	memset(buf, 0, sizeof(buf));
	memcpy((char *)ptr, buf, 11); //越界访问

	ptr[11] = 7; // 内存越界  
	memcpy(ptr +1, ptr, 11); // 踩内存  


	free(ptr);   
	free(ptr);// 重复释放  

	int *p1;  
	*p1 = 1; // 非法指针  
	printf("%d\n", ptr[8]);
}  

int main(void)  
{  
	test();  
	return 0;  
}

