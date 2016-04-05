/*************************************************************************
  > File Name: xx.c
  > Author: 
  > Mail: 
  > Created Time: Mon 04 Apr 2016 05:01:05 PM CST
  > Funciton:
 ************************************************************************/
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include <pthread.h>

struct msg {
	struct msg *m_next;
	/* ... more stuff here ... */
};

struct msg *workq;
//静态 条件变量和 互斥量
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;

pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void process_msg(void)
{
	struct msg *mp;

	for (;;) {
        printf("for  .....\n");
		pthread_mutex_lock(&qlock);
		while (workq == NULL){
			pthread_cond_wait(&qready, &qlock); // 等待ready信号，如果没有就阻塞这里，来了信号醒
            printf("while....\n");}
		mp = workq;
		workq = mp->m_next;
		pthread_mutex_unlock(&qlock);
		/* now process the message mp */
	}
}

void enqueue_msg(struct msg *mp)
{
	pthread_mutex_lock(&qlock);  // 消息放到队列需要锁住互斥量，在等待线程发送信号的时候，不需要互斥量
	mp->m_next = workq;
	workq = mp;
	pthread_mutex_unlock(&qlock);
                       // 消息放到队列需要锁住互斥量，在等待线程发送信号的时候，不需要互斥量
    printf("before qread siganl!\n");
	pthread_cond_signal(&qready);
}

int main()
{
    struct msg *mp = (struct msg *) malloc(sizeof(struct msg));
    //pthread_cond_signal(&qready); // 直接在这里发送信号是没用的
    enqueue_msg(mp);
    process_msg();
    sleep(1);
    pthread_cond_signal(&qready);
    enqueue_msg(mp);
    return 0;
}
