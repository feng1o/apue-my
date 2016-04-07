#include "unistd.h"
#include "stdio.h"
int main()
{
    printf("fd = %s \n", ttyname(0));
    return 0;
}
