#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>

//#define __NR_mysyscall 384

//__syscall0(long, mysyscall)

int main()
{
	long stack_size;
	stack_size = syscall(384);
	printf("user: the kernel stack size: %#x\n", stack_size);

	return 0;

}

