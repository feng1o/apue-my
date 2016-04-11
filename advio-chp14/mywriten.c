/*************************************************************************
    > File Name: mywriten.c
  > Author: 
  > Mail: 
  > Created Time: Sat 09 Apr 2016 11:18:02 PM CST
 ************************************************************************/

#include <stdio.h>
#include "unistd.h"
#include "fcntl.h"
#include "stdlib.h"

ssize_t writen(int  fd, void * buf, size_t n)
{
    size_t nleft = n;
    size_t nwrite;
    while(nleft > 0)
    {
    if((nwrite = write(fd, buf, nleft)) < 0 )
    {
        if(n == nleft)
            exit(-1);
        else
            break;
    }
    }
}
