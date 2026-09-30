#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd1, fd2;
    const char *filename = (argc > 1) ? argv[1] : "myfile";

    // 1. 파일 생성(creat, 권한 0600) 및 fd1 반환
    if ((fd1 = creat(filename, 0600)) == -1) {
        perror(filename);
        exit(1);
    }

    // 2. fd1으로 "Hello! Linux" 쓰기 (12바이트)
    write(fd1, "Hello! Linux", 12);

    // 3. fd1을 복제하여 fd2 생성
    fd2 = dup(fd1);

    // 4. 복제된 fd2로 "Bye! Linux" 쓰기 (10바이트)
    write(fd2, "Bye! Linux", 10);

    close(fd1);
    close(fd2);
    exit(0);
}
