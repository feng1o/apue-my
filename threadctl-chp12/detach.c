/*************************************************************************
  > File Name: xx.c
  > Author: 
  > Mail: 
  > Created Time: Mon 04 Apr 2016 05:01:05 PM CST
  > Funciton:
 ************************************************************************/
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include <pthread.h>

int makethreadAttr( void *(*fun)(void *), void *arg )
{
    pthread_t tid;
    pthread_attr_t   attr;

    if( pthread_attr_init( &attr ) )
        printf("error init  thread attr\n");
    if(!pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED))    
        if(pthread_create(&tid, &attr, fun, arg))
             printf("create detached pthread ok!\n");
    pthread_attr_destroy(&attr);
    return 0;
}
/*
int makethread(void *(*fn)(void *), void *arg)
{
	int				err;
	pthread_t		tid;
	pthread_attr_t	attr;

	err = pthread_attr_init(&attr);
	if (err != 0)
		return(err);
	err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if (err == 0)
		err = pthread_create(&tid, &attr, fn, arg);
	pthread_attr_destroy(&attr);
	return(err);
}
*/
