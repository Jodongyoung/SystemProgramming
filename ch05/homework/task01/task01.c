#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LEN 256

int main(int argc, char *argv[]) {
    int fd;
    char ch;
    char savedText[MAX_LINES][MAX_LEN];
    int line = 0, col = 0;
    char input[100];

    if (argc < 2) {
        fprintf(stderr, "사용법: %s [파일명]\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    // 힌트 2번: read()로 1바이트씩 읽으면서 '\n' 기준 2차원 배열에 저장
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

    // 마지막 줄에 '\n'이 없이 끝난 경우 처리
    if (col > 0) {
        savedText[line][col] = '\0';
        line++;
    }

    // 슬라이드 30페이지 실행 결과 화면 형식 출력
    printf("File read success\n");
    printf("Total Line : %d\n", line);
    printf("You can choose 1 ~ %d Line\n", line);
    printf("Pls 'Enter' the line to select : ");
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        exit(0);
    }

    // 개행 문자 제거
    input[strcspn(input, "\r\n")] = '\0';

    // 1. '*' 옵션 (모든 줄 출력 - 5점)
    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < line; i++) {
            printf("%s\n", savedText[i]);
        }
    }
    // 2. 'n-m' 옵션 (범위 출력 - 3점)
    else if (strchr(input, '-') != NULL) {
        int start = 0, end = 0;
        if (sscanf(input, "%d-%d", &start, &end) == 2) {
            for (int i = start; i <= end; i++) {
                if (i >= 1 && i <= line) {
                    printf("%s\n", savedText[i - 1]);
                }
            }
        }
    }
    // 3. 'n, ..., m' 옵션 (줄 번호 리스트 출력 - 2점)
    else if (strchr(input, ',') != NULL) {
        char *token = strtok(input, ", ");
        while (token != NULL) {
            int l_num = atoi(token);
            if (l_num >= 1 && l_num <= line) {
                printf("%s\n", savedText[l_num - 1]);
            }
            token = strtok(NULL, ", ");
        }
    }
    // 4. 'n' 옵션 (한 줄 출력 - 1점)
    else {
        int l_num = atoi(input);
        if (l_num >= 1 && l_num <= line) {
            printf("%s\n", savedText[l_num - 1]);
        }
    }

    exit(0);
}
