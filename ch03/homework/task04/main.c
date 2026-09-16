#include <stdio.h>
#include "print.h"
#include "word.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("사용법: %s <파일1> <파일2> ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        printfile(argv[i]);
        wc(argv[i]);
    }

    return 0;
}
