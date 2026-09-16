#include <stdio.h>
#include <string.h>
#include "copy.h"

int main() {
    char lines[5][MAXLINE];
    char temp[MAXLINE];

    printf("5개 문장을 입력하세요:\n");
    for (int i = 0; i < 5; i++) {
        if (fgets(lines[i], sizeof(lines[i]), stdin) != NULL) {
            lines[i][strcspn(lines[i], "\n")] = '\0';
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (strlen(lines[i]) > strlen(lines[j])) {
                copy(lines[i], temp);
                copy(lines[j], lines[i]);
                copy(temp, lines[j]);
            }
        }
    }

    printf("\n=== 길이순 정렬 결과 ===\n");
    for (int i = 0; i < 5; i++) {
        printf("%s (길이: %lu)\n", lines[i], strlen(lines[i]));
    }
    return 0;
}
