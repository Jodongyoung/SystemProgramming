#include <stdio.h>
#include <string.h>
#include "copy.h"

char line[MAXLINE];
char longest[MAXLINE];

int main() {
    int len;
    int max = 0;

    printf("문자열 입력 (종료: 빈 줄 엔터):\n");
    while (fgets(line, sizeof(line), stdin) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0) break;

        len = strlen(line);
        if (len > max) {
            max = len;
            copy(line, longest); // 조교 검사용 중단점 위치
        }
    }

    if (max > 0) printf("가장 긴 줄: %s\n", longest);
    return 0;
}