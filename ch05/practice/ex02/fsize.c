#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
    char buffer[BUFSIZE];
    int fd;
    ssize_t nread;
    long total = 0;

    if (argc < 2) {
        fprintf(stderr, "사용법: %s [file_name]\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    while ((nread = read(fd, buffer, BUFSIZE)) > 0) {
        total += nread;
    }

    close(fd);
    printf("%s file size : %ld byte\n", argv[1], total);
    exit(0);
}
