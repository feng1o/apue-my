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
