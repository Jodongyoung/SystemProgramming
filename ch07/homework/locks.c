#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int locks(int fd, int type, off_t offset, int whence, off_t len) {
    struct flock lock;

    lock.l_type = type;
    lock.l_whence = whence;
    lock.l_start = offset;
    lock.l_len = len;

    return fcntl(fd, F_SETLK, &lock);
}