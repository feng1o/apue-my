/*************************************************************************
    > File Name: xx.c
  > Author: 
  > Mail: 
  > Created Time: Fri 08 Apr 2016 03:10:31 PM CST
 ************************************************************************/
#include <stdio.h>
#include "stdlib.h"
#include "unistd.h"
#include <errno.h>
#include <fcntl.h>
#include "log_reg.h"
#include "error.h"
#include "tellwait.h"
#if 0
static sigset_t newmask, oldmask,zeromask;
static volatile sig_atomic_t  sigflag ;
static void sig_usr(int signo)	/* one signal handler for SIGUSR1 and SIGUSR2 */
{
	sigflag = 1;
}
void TELL_WAIT(void)
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		err_sys("signal(SIGUSR1) error");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		err_sys("signal(SIGUSR2) error");
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);
	sigaddset(&newmask, SIGUSR2);

	/* Block SIGUSR1 and SIGUSR2, and save current signal mask */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("SIG_BLOCK error");
}
#endif 
static void lockabyte(const char *name, int fd, off_t offset)
{
	if (log_reg(fd, F_SETLKW, F_WRLCK,  offset, SEEK_SET, 1) < 0)
		printf("%s: lock_reg error", name);
	printf("%s: got the lock, byte %lld\n", name, (long long)offset);
}

int
main(void)
{
	int		fd;
	pid_t	pid;

	/*
	 * Create a file and write two bytes to it.
	 */
	if ((fd = creat("templock", O_RDWR)) < 0)
		printf("creat error");
	if (write(fd, "ab", 2) != 2)
		printf("write error");

	TELL_WAIT();
	if ((pid = fork()) < 0) {
		printf("fork error");
	} else if (pid == 0) {			/* child */
		lockabyte("child", fd, 0);
		TELL_PARENT(getppid());
		WAIT_PARENT();
		lockabyte("child", fd, 1);
	} else {						/* parent */
		lockabyte("parent", fd, 1);
		TELL_CHILD(pid);
		WAIT_CHILD();
		lockabyte("parent", fd, 0);
	}
	exit(0);
}
