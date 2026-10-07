#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // 인자 부족 예외 처리
    if (argc < 3) {
        fprintf(stderr, "사용법: %s <기존 파일> <새 링크 파일>\n", argv[0]);
        exit(1);
    }

    // link(existing, new) 호출 및 미존재 파일 예외 처리
    if (link(argv[1], argv[2]) == -1) {
        perror(argv[1]);
        exit(1);
    }

    exit(0);
}
