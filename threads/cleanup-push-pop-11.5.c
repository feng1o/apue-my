/*************************************************************************
  > File Name: xx.c
  > Author: 
  > Mail: 
  > Created Time: Mon 04 Apr 2016 05:01:05 PM CST
  > Funciton:pthread_cleanup_push pthread_cleanup_pop
 ************************************************************************/
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include <pthread.h>
void cleanup(void *arg)
{
	printf("cleanup: %s\n", (char *)arg);
}

void *
thr_fn1(void *arg)
{
	printf("thread 1 start\n");
	pthread_cleanup_push(cleanup, "thread 1 first handler");
	pthread_cleanup_push(cleanup, "thread 1 second handler");
	printf("thread 1 push complete\n");
	if (arg)
		return((void *)1); //不能反悔，只能使用exitpthread
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return((void *)1);
}

void *
thr_fn2(void *arg)
{
	printf("thread 2 start\n");
	pthread_cleanup_push(cleanup, "thread 2 first handler");
	pthread_cleanup_push(cleanup, "thread 2 second handler");
	printf("thread 2 push complete\n");
	if (arg)
		pthread_exit((void *)2); // 会调用 cleanup
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit((void *)2);
}

int
main(void)
{
	int			err;
	pthread_t	tid1, tid2;
	void		*tret;

	err = pthread_create(&tid1, NULL, thr_fn1, (void *)1);
	if (err != 0)
		printf( "can't create thread 1");
	err = pthread_create(&tid2, NULL, thr_fn2, (void *)1);
	if (err != 0)
		printf( "can't create thread 2");
	err = pthread_join(tid1, &tret); //分离状态，阻塞等待tid1退出，，
	if (err != 0)
		printf( "can't join with thread 1");
	printf("thread 1 exit code %ld\n", (long)tret);
	err = pthread_join(tid2, &tret);
	if (err != 0)
		printf( "can't join with thread 2");
	printf("thread 2 exit code %ld\n", (long)tret);
	exit(0);
}
