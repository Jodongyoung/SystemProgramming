#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
    int fd1, fd2;
    ssize_t n;
    char buf[BUFSIZE];

    if (argc != 3) {
        fprintf(stderr, "사용법: %s file1 file2\n", argv[0]);
        exit(1);
    }

    // 1. 원본 파일 읽기 모드(O_RDONLY)로 열기
    if ((fd1 = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    // 2. 대상 파일 쓰기 모드(O_WRONLY | O_CREAT | O_TRUNC, 0600)로 생성
    if ((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1) {
        perror(argv[2]);
        close(fd1);
        exit(3);
    }

    // 3. read로 읽어온 바이트(n)만큼 write로 쓰기
    while ((n = read(fd1, buf, BUFSIZE)) > 0) {
        write(fd2, buf, n);
    }

    close(fd1);
    close(fd2);
    exit(0);
}
