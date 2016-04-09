#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "aio.h"
#include "fcntl.h"
#define  NBUF 8    //8 asynchrous io
int main(int argc, char* argv[])
{
    int ifd, ofd, i, j, n, err, numop;
    struct stat sbuf;  //file properity
    const struct aiocb *aiolist[NBUF];
    off_t   off = 0;

    if(argc != 3)
        perror("no infile, outfile...\n");
    if((ifd = open(argv[1],O_RDONLY)) < 0 )
        perror("infile open error \n"); 
    
    return 0;
}
