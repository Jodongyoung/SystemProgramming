#include <stdio.h>
#include <string.h>

void print_stream(FILE *fp, int show_line) {
    int c;
    int line = 1;
    int at_line_start = 1;

    while ((c = getc(fp)) != EOF) {
        if (show_line && at_line_start) {
            printf(" %d ", line++);
            at_line_start = 0;
        }
        putchar(c);
        if (c == '\n') {
            at_line_start = 1;
        }
    }
}

int main(int argc, char *argv[]) {
    int show_line = 0;
    int start_index = 1;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        show_line = 1;
        start_index = 2;
    }

    if (start_index >= argc) {
        print_stream(stdin, show_line);
    } else {
        for (int i = start_index; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                fprintf(stderr, "cat: %s: 그런 파일이나 디렉터리가 없습니다\n", argv[i]);
                continue;
            }
            print_stream(fp, show_line);
            fclose(fp);
        }
    }

    return 0;
}
