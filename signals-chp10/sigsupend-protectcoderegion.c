/*保护特定代码临界区，不被信号中断的实现方法*/
/*************************************************************************
  > File Name: pr_mask.c
  > Author:lf
  > Mail: 
  > Created Time: Sun 03 Apr 2016 03:51:16 PM CST
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

int main(void)
{
	sigset_t	newmask, oldmask, waitmask;
	pr_mask("program start: ");

	if (signal(SIGINT, sig_int) == SIG_ERR)
		printf("signal(SIGINT) error");
	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);

	// * Block SIGINT and save current signal mask.
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		printf("SIG_BLOCK error");

	//* Critical region of code.
	pr_mask("in critical region: ");

	// * Pause, allowing all signals except SIGUSR1.
	if (sigsuspend(&waitmask) != -1) //表示现在屏蔽waitmask的屏蔽字，解锁前面的屏蔽
		printf("sigsuspend error");

	pr_mask("after return from sigsuspend: ");

	// * Reset signal mask which unblocks SIGINT.
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		printf("SIG_SETMASK error");

	// * And continue processing ...
	pr_mask("program exit: ");
	exit(0);
}

static void sig_int(int signo)
{
	pr_mask("\nin sig_int: ");
}
