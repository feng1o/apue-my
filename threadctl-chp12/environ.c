#include"stdio.h"
#include"stdlib.h"
#include"unistd.h"

int main(int argc, char *argv[])
{
    int i;
    char ** ptr;
    extern char ** environ;

    for(i=0;i<argc;i++)
        printf("argv[%d]: %s \n",i , argv[i]);
    for(ptr = environ; *ptr != 0; ptr++)
        printf("%s\n", *ptr);

    printf("%d\n", sysconf(_SC_THREAD_SAFE_FUNCTIONS));

#if !defined(_POSIX_THREAD_SAFE_FUNCTIONS)
    printf("ok.......................\n");
#endif
#ifdef  _POSIX_THREAD_SAFE_FUNCTIONS
    printf("ok.......................\n");
#endif
    exit(0);
    }
