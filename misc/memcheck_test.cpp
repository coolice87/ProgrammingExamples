#include <stdlib.h>  
#include <malloc.h>  
#include <string.h>  
  
void test()  
{  
	    int *ptr =(int *) malloc(sizeof(int)*10);  
		  
			ptr = (int *)malloc(10);
			  
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

