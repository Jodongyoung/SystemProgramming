#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "사용법: %s <실제 파일> <심볼릭 링크 파일>\n", argv[0]);
        exit(1);
    }

    // symlink(actual, symlink) 호출 및 예외 처리
    if (symlink(argv[1], argv[2]) == -1) {
        perror(argv[1]);
        exit(1);
    }

    exit(0);
}
