#include "fcntl.h"
#include "stdio.h"

#define read_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLK, F_RDLK, (offset), (whence), (len))

int log_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return (fcntl(fd, cmd, &lock));
}

pid_t log_test(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    if(fcntl(fd, F_GETLK, &lock) < 0)
        perror("fcntl get errro \n");
    if(lock.l_type == F_UNLCK)
        return 0;
    return (lock.l_pid);
}
