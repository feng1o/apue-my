/*************************************************************************
  > File Name: pr_mask.c
  > Author:lf
  > Mail: 
  > Created Time: Sun 03 Apr 2016 03:51:16 PM CST
 ************************************************************************/
#include"stdio.h"
#include"stdlib.h"
#include"signal.h"
#include"unistd.h"

static void
sig_int(int signo)
{
	printf("caught SIGINT\n");
}

static void
sig_chld(int signo)
{
	printf("caught SIGCHLD\n");
}

int
main(void)
{
	if (signal(SIGINT, sig_int) == SIG_ERR)
		printf("signal(SIGINT) error");
	if (signal(SIGCHLD, sig_chld) == SIG_ERR)
		printf("signal(SIGCHLD) error");
	if (system("/bin/ed") < 0)
		printf("system() error");
	exit(0);
}
