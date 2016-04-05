#include <stdlib.h>
#include "unistd.h"
#include "stdio.h"
#include <pthread.h>

struct foo {
	int             f_count;
	pthread_mutex_t f_lock;
	int             f_id;
	/* ... more stuff here ... */
};

struct foo * foo_alloc(int id) /* allocate the object */
{
	struct foo *fp;
	if ((fp = (struct foo*)malloc(sizeof(struct foo))) != NULL) { // 分配空间
		fp->f_count = 1;
		fp->f_id = id;
		if (pthread_mutex_init(&fp->f_lock, NULL) != 0) { // 初始化，默认属性，
			free(fp);
			return(NULL);
		}
	}
	return(fp);
}

void foo_hold(struct foo *fp) /* add a reference to the object */
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele(struct foo *fp) /* release a reference to the object */
{
	pthread_mutex_lock(&fp->f_lock);
	if (--fp->f_count == 0) { /* last reference */
		pthread_mutex_unlock(&fp->f_lock);   //先解锁，然后destroy
		pthread_mutex_destroy(&fp->f_lock); // 动态分配的，需要都调用删除
		free(fp);
	} else {
		pthread_mutex_unlock(&fp->f_lock);
	}
}

void print_foo( struct foo* strf)
{
    printf("\n");
    printf("f_cont = %d \n", strf->f_count);
    printf("f_lock = %d \n", strf->f_lock);
    printf("f_id   = %d \n", strf->f_id);
    printf("f_cont = %d \n", strf->f_count);
}
int main()
{
    struct foo * strf = foo_alloc(1);
    print_foo(strf);
    foo_hold(strf);
    print_foo(strf);
    foo_hold(strf);
    print_foo(strf);
    foo_rele(strf);
    print_foo(strf);
    foo_rele(strf);
    print_foo(strf);
    foo_rele(strf);
    print_foo(strf);
    sleep(1);
    int a = 1;
    foo_rele(strf);
    print_foo(strf);
    return 0;
}
