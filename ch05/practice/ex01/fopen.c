#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd;

    if (argc < 2) {
        fprintf(stderr, "사용법: %s [file_name]\n", argv[0]);
        exit(1);
    }

    // 읽기/쓰기 모드(O_RDWR)로 파일 열기
    if ((fd = open(argv[1], O_RDWR)) == -1) {
        printf("파일 열기 오류\n");
        exit(2);
    } else {
        // 슬라이드 7페이지 결과 문구와 동일하게 출력
        printf("file %s open success: %d\n", argv[1], fd);
    }

    close(fd);
    exit(0);
}
