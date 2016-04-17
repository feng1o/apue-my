/*************************************************************************
    > File Name: tryconnect.c
  > Author: 
  > Mail: 
  > Created Time: Fri 15 Apr 2016 10:27:25 AM CST
 ************************************************************************/
#include "stdio.h"
#include "sys/socket.h"
#include "unistd.h"
#define def_MAXSLEEP 128

int connect_retry(int domain, int type, int protocol, const struct sockaddr * addr, socklen_t alen)
{
    int fd;
    int numsec;
    for(numsec = 1; numsec < def_MAXSLEEP; ++numsec)
    {
        if((fd = socket(domain, type, protocol))<0)     
            return(-1);
         printf("try connect =%d\n", numsec);
        if(connect(fd, addr, alen)==0)
          return  fd;

        close(fd);
         if(numsec < def_MAXSLEEP/2)     
         sleep(numsec);
    }
    return -1;

}
