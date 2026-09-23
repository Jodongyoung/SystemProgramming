#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main(int argc, char *argv[]) {
    struct student rec;
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "사용법: %s 파일이름\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "w");
    if (fp == NULL) {
        fprintf(stderr, "파일 열기 오류\n");
        return 2;
    }

    printf("%-9s %-7s %-4s\n", "학번", "이름", "점수");
    while (scanf("%d %s %d", &rec.id, rec.name, &rec.score) == 3) {
        fprintf(fp, "%d %s %d ", rec.id, rec.name, rec.score);
    }

    fclose(fp);
    return 0;
}
