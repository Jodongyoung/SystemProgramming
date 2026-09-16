#include <stdio.h>
#include <string.h>
#include "copy.h"

#define NUM_LINES 5

int main() {
    char lines[NUM_LINES][MAXLINE];
    char temp[MAXLINE];

    printf("5개 문장을 입력하세요:\n");
    for (int i = 0; i < NUM_LINES; i++) {
        if (fgets(lines[i], sizeof(lines[i]), stdin) != NULL) {
            lines[i][strcspn(lines[i], "\n")] = '\0';
        }
    }

    // 길이순(오름차순) 버블/선택 정렬 (copy 모듈 활용)
    for (int i = 0; i < NUM_LINES - 1; i++) {
        for (int j = i + 1; j < NUM_LINES; j++) {
            if (strlen(lines[i]) > strlen(lines[j])) {
                copy(lines[i], temp);
                copy(lines[j], lines[i]);
                copy(temp, lines[j]);
            }
        }
    }

    printf("\n=== 길이순 정렬 결과 ===\n");
    for (int i = 0; i < NUM_LINES; i++) {
        printf("%s (길이: %lu)\n", lines[i], strlen(lines[i]));
    }
    return 0;
}
