#include <sys/types.h>
#include <utime.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    struct stat buf;
    struct utimbuf time;

    if (argc < 3) {
        fprintf(stderr, "사용법: %s <원본파일> <대상파일>\n", argv[0]);
        exit(1);
    }

    // 1. 원본 파일 상태(시간 정보) 가져오기
    if (stat(argv[1], &buf) < 0) {
        perror("stat()");
        exit(-1);
    }

    // 2. 시간 정보 복사 구조체에 담기
    time.actime = buf.st_atime;
    time.modtime = buf.st_mtime;

    // 3. 대상 파일에 시간 덮어씌우기
    if (utime(argv[2], &time)) {
        perror("utime");
        exit(-1);
    }

    exit(0);
}
