#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LINES 100
#define MAX_LEN 256

int main(int argc, char *argv[]) {
    int fd;
    char ch;
    char savedText[MAX_LINES][MAX_LEN];
    int line = 0, col = 0;

    if (argc < 2) {
        fprintf(stderr, "사용법: %s [파일명]\n", argv[0]);
        exit(1);
    }

    // 1. 원본 파일 읽기 전용(O_RDONLY)으로 열기
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    // 2. read()로 1바이트씩 읽으면서 '\n' 기준 2차원 배열에 각 행 저장
    while (read(fd, &ch, 1) > 0) {
        if (ch == '\n') {
            savedText[line][col] = '\0';
            line++;
            col = 0;
            if (line >= MAX_LINES) break;
        } else {
            if (col < MAX_LEN - 1) {
                savedText[line][col++] = ch;
            }
        }
    }
    close(fd);

    // 마지막 줄 끝에 '\n'이 없었을 경우의 예외 처리
    if (col > 0) {
        savedText[line][col] = '\0';
        line++;
    }

    // 3. 마지막 줄부터 첫 번째 줄까지 거꾸로 출력
    for (int i = line - 1; i >= 0; i--) {
        printf("%s\n", savedText[i]);
    }

    exit(0);
}
