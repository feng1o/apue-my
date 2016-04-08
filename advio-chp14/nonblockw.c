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

char	buf[500000];

void set_fl(int fd, int flags)
{
    int val ;
    if((val = fcntl(fd,F_GETFL, 0))<0) //获取文件描述符FLAG
        perror("get flag  error\n");
    val |= flags;                     //falg合并
    if(fcntl(fd, F_SETFL, val) < 0)  //设置flag
    perror("set flag error \n");
}
void clr_fl(int fd, int flags)
{
    int val ;
    if((val = fcntl(fd,F_GETFL, 0))<0) //获取文件描述符FLAG
        perror("get flag  error\n");
    val &= ~flags;                     //falg合并
    if(fcntl(fd, F_SETFL, val) < 0)  //设置flag
        perror("set flag error \n");
}
int main(void)
{
	int		ntowrite, nwrite;
	char	*ptr;

	ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
	fprintf(stderr, "read %d bytes\n", ntowrite);
    printf("\n................read......\n");
    sleep(1);
	set_fl(STDOUT_FILENO, O_NONBLOCK);	/* set nonblocking */

	ptr = buf;
	while (ntowrite > 0) {
		errno = 0;
		nwrite = write(STDOUT_FILENO, ptr, ntowrite);
		fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);
        printf("nwrite ...%d\n\n",nwrite);
        sleep(1);
		if (nwrite > 0) {
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}

	clr_fl(STDOUT_FILENO, O_NONBLOCK);	/* clear nonblocking */

	exit(0);
}
