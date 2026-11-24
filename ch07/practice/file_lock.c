#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd;

    // 1. 인자 개수 예외 처리
    if (argc < 2) {
        fprintf(stderr, "사용법 : %s 파일이름\n", argv[0]);
        exit(1);
    }

    // 2. 파일 열기 (없으면 생성)
    if ((fd = open(argv[1], O_RDWR | O_CREAT, 0644)) == -1) {
        perror(argv[1]);
        exit(1);
    }

    // 3. lockf()를 사용하여 파일 잠금 수행 (잠금 불가 시 -1 반환 예외처리)
    if (lockf(fd, F_LOCK, 0) == -1) {
        perror(argv[1]);
        close(fd);
        return -1;
    }

    // 4. 슬라이드 15번 실행 결과처럼 success 출력 후 잠금 상태 유지
    printf("success\n");

    // 다른 터미널에서 ls >> 파일명 테스트를 할 수 있도록 종료하지 않고 대기
    pause();

    close(fd);
    return 0;
}