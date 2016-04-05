/*************************************************************************
  > File Name: pr_mask.c
  > Author:lf
  > Mail: 
  > Created Time: Sun 03 Apr 2016 03:51:16 PM CST
  > Funciton: 等待一个信号处理函数设置一个全局变量
 ************************************************************************/
#include "signal.h" 
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "errno.h"

static void	sig_int(int);
void pr_mask(const char * str)
{
    sigset_t sigset; //信号集
    int      errno_save;//errno 

    errno_save = errno;
    if(sigprocmask(0, NULL, &sigset) < 0){
        printf("sigprocmask error\n");
    
    }
    else {
        printf("%s", str);
        if(sigismember(&sigset, SIGINT))
            printf("sigint");
        if(sigismember(&sigset, SIGQUIT))
             printf("sigquit");

        if(sigismember(&sigset, SIGUSR1))
            printf("SIGUSR1");
         if(sigismember(&sigset, SIGALRM))
            printf("sigalrm");
}
    printf("\n");
    errno = errno_save;
}


volatile sig_atomic_t	quitflag;	/* set nonzero by signal handler */

static void sig_int(int signo)	/* one signal handler for SIGINT and SIGQUIT */
{
	if (signo == SIGINT)
		printf("\ninterrupt\n");
	else if (signo == SIGQUIT)
		quitflag = 1;	/* set flag for main loop */
}

int main(void)
{
	sigset_t	newmask, oldmask, zeromask;
	if (signal(SIGINT, sig_int) == SIG_ERR)
		printf("signal(SIGINT) error");
	if (signal(SIGQUIT, sig_int) == SIG_ERR)
		printf("signal(SIGQUIT) error");

	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	/*
	 * Block SIGQUIT and save current signal mask.
	 */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		printf("SIG_BLOCK error");
	while (quitflag == 0)
		sigsuspend(&zeromask);
	/*
	 * SIGQUIT has been caught and is now blocked; do whatever.
	 */
	quitflag = 0;
	/*
	 * Reset signal mask which unblocks SIGQUIT.
	 */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		printf("SIG_SETMASK error");
    printf("exit......\n");
	exit(0);
}
