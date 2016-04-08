#makefile
CC=gcc
cflag= -Wall -g
source=tellwait.h deadlock.c  log_reg.h error.h
all:$(source)
	$(CC) $(cflag) $^  -o a.out
.PHONY:clean
clean:
	ls | grep -Ev  ".[c]$|.[h]$|makefile"
