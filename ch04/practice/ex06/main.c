#include <stdio.h>
#include <string.h>
#include "student.h"

int main(int argc, char *argv[]) {
    struct student rec;
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "사용법: %s 파일이름\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "wb");
    if (fp == NULL) {
        fprintf(stderr, "파일 %s 열기 오류\n", argv[1]);
        return 2;
    }

    printf("%10s %6s %6s\n", "학번", "이름", "점수");
    memset(&rec, 0, sizeof(rec));

    while (scanf("%d %s %hd", &rec.id, rec.name, &rec.score) == 3) {
        fwrite(&rec, sizeof(rec), 1, fp);
        memset(&rec, 0, sizeof(rec));
    }

    fclose(fp);
    return 0;
}
