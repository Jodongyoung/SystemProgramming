#include <stdio.h>

/* 텍스트 파일 내용을 표준 출력에 출력 */
int main(int argc, char *argv[]) {
    FILE *fp;
    int c;

    // 명령줄 인수가 없으면 표준 입력 사용S
    if (argc < 2) {
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            fprintf(stderr, "파일 %s 열기 오류\n", argv[1]);
            return 1;
        }
    }

    c = getc(fp);
    while (c != EOF) {
        putc(c, stdout);
        c = getc(fp);
    }

    if (fp != stdin) {
        fclose(fp);
    }
    return 0;
}
