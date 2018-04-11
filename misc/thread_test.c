/* 说明:
 * thread1/thread2: SCHED_RR or SCHED_FIFO, thread3: normal
 * thread1实时优先级高于thread2, CPU个数4核
 * CPU_NUM用于分别创建thread1 thread2 thread3个数
 * 当CPU_NUM=1时, thread1 thread2 thread3 在3个核上运行，1个核空闲
 * 当CPU_NUM=2时, thread1 thread2分别占据2个核运行,偶尔运行thread3
 * 当CPU_NUM=3时, thread1占据3个核, thread2占据1个核, 偶尔运行thread3
 * 当CPU_NUM>=4时, thread1 占据4个核, thread2得不到运行, 偶尔运行thread3
 * 问题: 为啥thread3会得到运行？
 * 答：
 * pick_next_task里:先执行了CFS调度类查找,再按照运行队列本身的调度类进行查找
 * */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#define CPU_NUM 	4
#define LOOP_FOREVER

void mdelay(uint32_t ms)
{
	uint32_t i,j;
	for(i=0; i<ms; i++){
		for(j=0; j<100000; j++){
			;
		}
	}
}

void Thread1()
{
	sleep(1);
	int i,j;
	int policy;
	struct sched_param param;
	pthread_getschedparam(pthread_self(),&policy,&param);
	if(policy == SCHED_OTHER)
		printf("SCHED_OTHER 1\n");
	if(policy == SCHED_RR);
		printf("SCHED_RR 1 \n");
	if(policy==SCHED_FIFO)
		printf("SCHED_FIFO 1\n");

#ifdef LOOP_FOREVER
	for(;;)
#else
	for(i=1;i<5;i++)
#endif
	{
		mdelay(1000);
		printf("thread 1\n");
	}
	printf("Pthread 1 exit\n");
}

void Thread2()
{
	sleep(1);
	int i,j,m;
	int policy;
	struct sched_param param;
	pthread_getschedparam(pthread_self(),&policy,&param);
	if(policy == SCHED_OTHER)
		printf("SCHED_OTHER 2\n");
	if(policy == SCHED_RR);
		printf("SCHED_RR 2\n");
	if(policy==SCHED_FIFO)
		printf("SCHED_FIFO 2\n");
#ifdef LOOP_FOREVER
	for(;;)
#else
	for(i=1;i<5;i++)
#endif
	{
		mdelay(1000);
		printf("thread 2\n");
	}
	printf("Pthread 2 exit\n");
}

void Thread3()
{
	sleep(1);
	int i,j;
	int policy;
	struct sched_param param;
	pthread_getschedparam(pthread_self(),&policy,&param);
	if(policy == SCHED_OTHER)
		printf("SCHED_OTHER 3\n");
	if(policy == SCHED_RR)
		printf("SCHED_RR 3\n");
	if(policy==SCHED_FIFO)
		printf("SCHED_FIFO 3\n");
#ifdef LOOP_FOREVER
	for(;;)
#else
	for(i=1;i<5;i++)
#endif
	{
		mdelay(1000);
		printf("thread 3\n");
	}
	printf("Pthread 3 exit\n");
}

int main()
{
	int i;
	i = getuid();
	if(i==0)
		printf("The current user is root\n");
	else
		printf("The current user is not root\n");

	pthread_t ppid1[CPU_NUM];
	pthread_t ppid2[CPU_NUM];
	pthread_t ppid3[CPU_NUM];
	struct sched_param param;

	pthread_attr_t attr,attr1,attr2;

	pthread_attr_init(&attr1);
	pthread_attr_init(&attr);
	pthread_attr_init(&attr2);
	param.sched_priority = 51;
	pthread_attr_setschedpolicy(&attr2,SCHED_RR);
	pthread_attr_setschedparam(&attr2,&param);
	pthread_attr_setinheritsched(&attr2,PTHREAD_EXPLICIT_SCHED);//要使优先级其作用必须要有这句话

	param.sched_priority = 21;
	pthread_attr_setschedpolicy(&attr1,SCHED_RR);
	pthread_attr_setschedparam(&attr1,&param);
	pthread_attr_setinheritsched(&attr1,PTHREAD_EXPLICIT_SCHED);

	for(i=0; i<CPU_NUM; i++)
	{
		pthread_create(&ppid3[i],&attr,(void *)Thread3,NULL);
		pthread_create(&ppid2[i],&attr1,(void *)Thread2,NULL);
		pthread_create(&ppid1[i],&attr2,(void *)Thread1,NULL);
	}

	for(i=0; i<CPU_NUM; i++)
	{
		pthread_join(ppid3[i],NULL);
		pthread_join(ppid2[i],NULL);
		pthread_join(ppid1[i],NULL);
	}

	pthread_attr_destroy(&attr2);
	pthread_attr_destroy(&attr1);
	return 0;
}

