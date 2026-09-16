#include <stdio.h>
#include "Read.h"
void read_file(const char *filename) {
    char buffer[256];
    FILE *fp = fopen(filename, "r");
    if (!fp) return;
    printf("\n--- [%s] 파일 내용 출력 ---\n", filename);
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    fclose(fp);
}
