#include "unistd.h"
#include "signal.h"
#include "fcntl.h"
#include "stdlib.h"
#include "stdio.h"

#define MAXLINE 100
static void	sig_alrm(int);

int
main(void)
{
	int		n;
	char	line[MAXLINE];

	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		printf("signal(SIGALRM) error");

	alarm(10);
	if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
		printf("read error");
	alarm(0); //如果没有输入，等待10秒回alram信号，如果正在
    //读取的时候，alram到了，会使得wreite一直阻塞在哪里

	write(STDOUT_FILENO, line, n);
	exit(0);
}

static void
sig_alrm(int signo)
{
    printf("arlairm handler \n\n");
	/* nothing to do, just return to interrupt the read */
}
