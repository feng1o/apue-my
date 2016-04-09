#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "stdlib.h"

#define MAXLINE 4096
int main(void)
{
	int		n;
	int		fd[2]; //文件描述符2
	pid_t	pid;
	char	line[MAXLINE];

	if (pipe(fd) < 0) //创建管道
		printf("pipe error");
	if ((pid = fork()) < 0) {
		printf("fork error");
	} else if (pid > 0) {		/* parent */
		close(fd[0]);    //关闭了读 write to subprocess
		write(fd[1], "hello world\n", 12);
	} else {					/* child */
		close(fd[1]);   //close write,,,just read zhe pipe
		n = read(fd[0], line, MAXLINE);
		write(STDOUT_FILENO, line, n);  //write the data to stdout,,,
	}
	exit(0);
}
