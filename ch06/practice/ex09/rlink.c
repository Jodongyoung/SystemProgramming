#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char buffer[1024];
    int nread;

    // 1. 인자 확인 예외 처리
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <심볼릭 링크 파일>\n", argv[0]);
        exit(1);
    }

    // 2. readlink() 호출 및 예외 처리
    nread = readlink(argv[1], buffer, sizeof(buffer) - 1);
    if (nread < 0) {
        perror(argv[1]);
        exit(1);
    }

    // 3. 문자열 끝에 널 문자(\0) 추가 후 출력
    buffer[nread] = '\0';
    printf("%s\n", buffer);

    exit(0);
}
