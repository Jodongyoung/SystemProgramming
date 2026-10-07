#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int newmode;

    // 인자 부족 예외 처리
    if (argc < 3) {
        fprintf(stderr, "사용법: %s <8진수 모드> <파일명>\n", argv[0]);
        exit(1);
    }

    // 8진수 문자열을 모드 값으로 변환
    newmode = (int) strtol(argv[1], (char **) NULL, 8);

    // 파일 권한 변경 및 미존재 예외 처리
    if (chmod(argv[2], newmode) == -1) {
        perror(argv[2]);
        exit(1);
    }

    exit(0);
}
