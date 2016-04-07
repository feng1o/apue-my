#include"stdlib.h"
#include"stdio.h"
#include"unistd.h"
//#include"sys/types.h"

int main()
{
    pid_t id;
    id = fork();
    if(id != 0)
        printf("id != 0 ===%d\n",id);
    printf("uid = %d, euid =%d\n", getuid(),geteuid());
    system("ls");
    system("date");
    printf("%d\n",system(NULL));
    printf("nice = %d\n",nice(100000));
    return 0;
}
