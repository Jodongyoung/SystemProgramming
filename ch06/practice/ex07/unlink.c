#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // 인자가 전달되지 않은 경우 사용법 출력
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <삭제할 링크 파일>\n", argv[0]);
        exit(1);
    }

    // unlink() 시스템 콜 호출 및 실패 시 예외 처리
    if (unlink(argv[1]) == -1) {
        perror(argv[1]);
        exit(1);
    }

    exit(0);
}
