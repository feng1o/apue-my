#include "stdio.h"

int main()
{
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	int a, b,c;
	char  *str = (char*) malloc(10);
	scanf("%d %d %d",  &a, &b, &c);
	printf("str = %s, a= %d ,b =%d, c=%d\n",str, a,b, c);
	return 0;
}
