#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
void init_daemon()
{
   pid_t pid ;
   int i ;
   pid =fork();
   if(pid<0)
   {
       printf("fork error secondly!\n");
       exit(1);
   }
   else if(pid>0)//结束父进程
   {
       printf("this is first parent process!\n");
       exit(0);
   }//子进程继续运行
   setsid() ;//前面为setsid正确调用提供了前提，使子进程成为新的会话组长和
         //新的进程组长
   pid=fork();
   if(pid<0)//子进程成为无终端的会话组长，但是还是可以打开终端，为了
          //使进程脱离终端，使之成为不是会话组长
   {
       printf(" fork error secondly!\n");
       exit(1);
   }
   else if(pid>0)//关闭第一个子进程
   {
        printf("this is first child process!\n");
        exit(0);
   }//第二个子进程继续运行
   for(i=0;i<NOFILE;i++)
   {
      close(i);
   }
   chdir("/tmp");
   umask(0);
   return;
}

//main.c
#include <stdio.h>
#include <stdlib.h>
void init_daemon(void);

int main(void)
{
     FILE *fp ;
     init_daemon() ;
     while(1)
     {
          if((fp=fopen("daemon.log","a"))>=0)
      {
          fprintf(fp,"%s","good");
          fclose(fp);
          sleep(10);
      }
     
     }
     exit(0);
}

