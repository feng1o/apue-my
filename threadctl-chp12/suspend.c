#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"
#include "signal.h"
#include <pthread.h>

int			quitflag;	/* set nonzero by thread */
sigset_t	mask; // 信号集
//静态初始化
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitloc = PTHREAD_COND_INITIALIZER;

void * thr_fn(void *arg)
{
	int err, signo;
	for (;;) {
		err = sigwait(&mask, &signo);
		if (err != 0)
			printf( "sigwait failed");
        printf("sigwait...\n");
		switch (signo) {
		case SIGINT:
			printf("\ninterrupt\n");
			break;

		case SIGQUIT:
			pthread_mutex_lock(&lock);
			quitflag = 1;
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&waitloc);
			return(0);

		default:
			printf("unexpected signal %d\n", signo);
			exit(1);
		}
	}
}

int
main(void)
{
	int			err;
	sigset_t	oldmask;
	pthread_t	tid;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	if ((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0)// 加入线程屏蔽字，init，quit被屏蔽，加入到默认屏蔽里面
		printf( "SIG_BLOCK error");

	err = pthread_create(&tid, NULL, thr_fn, 0); //创建线程
	if (err != 0)
		printf( "can't create thread");

	pthread_mutex_lock(&lock);
	while (quitflag == 0)
		pthread_cond_wait(&waitloc, &lock);
	pthread_mutex_unlock(&lock);

	/* SIGQUIT has been caught and is now blocked; do whatever */
	quitflag = 0;

	/* reset signal mask which unblocks SIGQUIT */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		printf("SIG_SETMASK error");
	exit(0);
}
