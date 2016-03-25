/*************************************************************************
  > File Name: myfile.c
  > Author: 
  > Mail: 
  > Created Time: Thu 24 Mar 2016 04:40:29 PM CST
 ************************************************************************/

#include<stdio.h>
#include"fcntl.h"
#include"stdlib.h"
#include"unistd.h"
int main()
{
    //int fd = open("./test.txt", O_WRONLY & O_RDONLY|O_CREAT);
    int fd = open("./test.txt", O_RDWR|O_CREAT);
    char *str = (char*)malloc(sizeof(char)*100);
    //char *str;

    if(creat("test2.txt", O_WRONLY)<0) 
        fprintf(stderr, "creat error\n");
    fprintf(stderr, "created\n ");
    
    write(fd,"writetest",2);
    printf("write bytes = %d\n",write(fd,"writetest...............write...",2));
    sync(); //synchrous stdin cache to disk file,
    fsync(fd);
    lseek(fd, 2, SEEK_CUR); //return 2
    read(fd, str, 30); //lseek ,ignored 2 char
    printf("str = %s\n", str);

    //fflush(stdin);
#if 0
    char ch;
    do{
       ch =  fgetc(stdin);
       putchar(ch);
    }
    while(ch != '\n' && ch !=  EOF);
#endif

    char *str2 = (char*)malloc(sizeof(char)*100);
    char *str3 = (char*)malloc(sizeof(char)*100);

    setbuf(stdin, NULL);  //can clear stdin in linu;

    read(STDIN_FILENO, str2, 100);
    write(STDOUT_FILENO, str2, 100);


    lseek(fd, 0, SEEK_SET); //return 2
    int fd2 = dup(fd); // duplicate fd,,
    int fd3 = dup2(fd, 10);
    read(10, str3, 10);
    printf("read fd3 = %s\n", str3);
    close(fd);
    return 0;
}

