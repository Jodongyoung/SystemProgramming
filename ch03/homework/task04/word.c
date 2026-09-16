#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "word.h"

void wc(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        return;
    }

    int chars = 0, words = 0, lines = 0;
    int in_word = 0;
    int c;

    while ((c = getc(fp)) != EOF) {
        chars++;
        if (c == '\n') {
            lines++;
        }
        if (isspace(c)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }
    fclose(fp);

    printf("--- [%s 통계 (wc)] ---\n", filename);
    printf("줄(lines): %d | 단어(words): %d | 글자(chars): %d\n", lines, words, chars);
}
