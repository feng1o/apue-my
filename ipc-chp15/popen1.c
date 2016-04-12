#include "stdio.h"
#include "stdlib.h"
#include <sys/wait.h>

#define MAXLINE 4096 
int main(void)
{
	char	line[MAXLINE];
	FILE	*fpin;

	if ((fpin = popen("./myuclc", "r")) == NULL) //一个程序:w
		printf("popen error");
	for ( ; ; ) {
		fputs("prompt> ", stdout);
		fflush(stdout);
		if (fgets(line, MAXLINE, fpin) == NULL)	/* read from pipe */
			break;
		if (fputs(line, stdout) == EOF)
			printf("fputs error to pipe");
	}
	if (pclose(fpin) == -1)
		printf("pclose error");
	putchar('\n');
	exit(0);
}
