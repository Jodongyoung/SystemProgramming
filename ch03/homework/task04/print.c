#include <stdio.h>
#include <stdlib.h>
#include "print.h"

void printfile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        return;
    }
    char buffer[256];
    printf("\n--- [%s 내용 출력] ---\n", filename);
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, stdout);
    }
    fclose(fp);
}
