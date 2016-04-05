/*************************************************************************
  > File Name: xx.c
  > Author: 
  > Mail: 
  > Created Time: Mon 04 Apr 2016 05:01:05 PM CST
  > Funciton: pthread_exit错误的退出后，期中线程栈上的数据无效，后续线程join获取其参数是错误的，无效的
 ************************************************************************/
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include <pthread.h>

struct foo {
	int a, b, c, d;
};

void
printfoo(const char *s, const struct foo *fp)
{
	printf("%s", s);
	printf("  structure at 0x%lx\n", (unsigned long)fp);
	printf("  foo.a = %d\n", fp->a);
	printf("  foo.b = %d\n", fp->b);
	printf("  foo.c = %d\n", fp->c);
	printf("  foo.d = %d\n", fp->d);
}

void *
thr_fn1(void *arg)
{
	struct foo	foo = {1, 2, 3, 4};

	printfoo("thread 1:\n", &foo);
	pthread_exit((void *)&foo);
}

void *
thr_fn2(void *arg)
{
	printf("thread 2: ID is %lu\n", (unsigned long)pthread_self()); //已经是无效的了，fn1的已经不存在
	pthread_exit((void *)0);
}

int
main(void)
{
	int			err;
	pthread_t	tid1, tid2;
	struct foo	*fp;

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err != 0)
		printf("can't create thread 1");
	err = pthread_join(tid1, (void *)&fp);
	if (err != 0)
		printf("can't join with thread 1");
	sleep(1);
	printf("parent starting second thread\n");
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err != 0)
		printf("can't create thread 2");
	sleep(1);
	printfoo("parent:\n", fp);
	exit(0);
}
