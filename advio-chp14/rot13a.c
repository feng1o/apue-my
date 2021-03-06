/*************************************************************************
    > File Name: xx.c
  > Author: 
  > Mail: 
  > Created Time: Fri 08 Apr 2016 03:10:31 PM CST
 ************************************************************************/
#include <stdio.h>
#include "stdlib.h"
#include "unistd.h"
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include <fcntl.h>

#define BSZ 4096

unsigned char buf[BSZ];

unsigned char translate(unsigned char c)
{
	if (isalpha(c)) {
		if (c >= 'n')
			c -= 13;
		else if (c >= 'a')
			c += 13;
		else if (c >= 'N')
			c -= 13;
		else
			c += 13;
	}
	return(c);
}

int main(int argc, char* argv[])
{
	int	ifd, ofd, i, n, nw;
	if (argc != 3)
		printf("usage: rot13 infile outfile");
	if ((ifd = open(argv[1], O_RDONLY)) < 0)
		printf("can't open %s", argv[1]);
	if ((ofd = open(argv[2], O_RDWR|O_CREAT|O_TRUNC,O_NONBLOCK )) < 0)
		printf("can't create %s", argv[2]);
	while ((n = read(ifd, buf, BSZ)) > 0) {
		for (i = 0; i < n; i++)
			buf[i] = translate(buf[i]);
		if ((nw = write(ofd, buf, n)) != n) {
			if (nw < 0)
				printf("write failed");
			else
				printf("short write (%d/%d)", nw, n);
		}
	}
	fsync(ofd);
	exit(0);
}
