#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"

void daemon_init(void)
{
    pid_t pid;
    if((pid=fork()) < 0) //创建进程,然后脱离父进程
    perror("fork error\n");
    else if(pid != 0)
        exit(0);//让父进程关闭，然后子进程创建会话

    setsid();
    if(chdir("/")<0)
    {
        perror("chdir  errror");
        exit(1);
    }

    umask(0);
    close(0);
    //0,1,2 > null
    open("/dev/null", O_RDWR);
    dup2(0,1);
    dup2(0,2);
}
int main()
{
    daemon_init();
    while(1);
    return 0;
}
