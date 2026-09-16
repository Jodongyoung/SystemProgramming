#include <stdio.h>
#include "Write.h"
void write_file(const char *filename, const char *content) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    fprintf(fp, "%s", content);
    fclose(fp);
}
