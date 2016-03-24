/*************************************************************************
    > File Name: myfile.c
  > Author: 
  > Mail: 
  > Created Time: Thu 24 Mar 2016 04:40:29 PM CST
 ************************************************************************/

#include<stdio.h>
#include"fcntl.h"
#include"unistd.h"
int main()
{
    int fd = open("./test.txt", O_WRONLY|O_RDONLY|O_CREAT);

    if(creat("test2.txt", O_WRONLY)<0) 
        fprintf(stderr, "creat error");
    fprintf(stderr, "created ");
    write(fd,"write....",10);
    close(fd);
    return 0;
}

