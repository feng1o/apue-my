#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pwd.h"
#include "signal.h"
#include "string.h"

static void myAlarm(int signo)
{
    struct passwd*  rootptr;

    printf("in signal handler \n");
    if((rootptr = getpwnam("root"))== NULL)
        perror("getpwnam  roort error");
//    printf("handler getpwanm = %s\n\n",rootptr->pw_name);
    alarm(1);
}
int main()
{
    struct passwd* ptr;
    signal(SIGALRM, myAlarm);
    alarm(1);
    for(;;)
    {
        //sleep(1);
        if((getpwnam("win8"))==NULL)
            printf("getpwnam  win 8 errorr \n");
        if(strcmp(ptr->pw_name, "win8") != 0)
            printf("getptrname =%s \n",ptr->pw_name);
    }
}
