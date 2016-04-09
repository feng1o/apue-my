#include <sys/wait.h>
#include "string.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "stdlib.h"

#define MAXLINE 4096
#define	DEF_PAGER	"/bin/more"		/* default pager program */

int main(int argc, char *argv[])
{
	int		n;
	int		fd[2];
	pid_t	pid;
	char	*pager, *argv0;
	char	line[MAXLINE];
	FILE	*fp;

	if (argc != 2)
		perror("usage: a.out <pathname>");

	if ((fp = fopen(argv[1], "r")) == NULL) //打开对应文件
		printf("can't open %s", argv[1]);
	if (pipe(fd) < 0)  //创建管道
		printf("pipe error");

	if ((pid = fork()) < 0) {
		printf("fork error");
	} else if (pid > 0) {								/* parent */
		close(fd[0]);		/* 父进程关闭读，父进程写close read end */

		/* parent copies argv[1] to pipe */
		while (fgets(line, MAXLINE, fp) != NULL) { //写数据到到line里面，，
			n = strlen(line);
			if (write(fd[1], line, n) != n) // 父进程写数据进管道
				printf("write error to pipe");
		}
		if (ferror(fp))
			printf("fgets error");

		close(fd[1]);	/* close write end of pipe for reader 父进程关闭写  */

		if (waitpid(pid, NULL, 0) < 0) //父进程等待获取子进程信息
			printf("waitpid error");
		exit(0);
    } 
    else
    {										/* child */
		close(fd[1]);	/* close write end */
		if (fd[0] != STDIN_FILENO) {
			if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
				printf("dup2 error to stdin");
			close(fd[0]);	/* don't need this after dup2 */
		}

		/* get arguments for execl() */
		if ((pager = getenv("PAGER")) == NULL)
			pager = DEF_PAGER;
		if ((argv0 = strrchr(pager, '/')) != NULL)
			argv0++;		/* step past rightmost slash */
		else
			argv0 = pager;	/* no slash in pager */

		if (execl(pager, argv0, (char *)0) < 0)
			printf("execl error for %s", pager);
	}
	exit(0);
}
