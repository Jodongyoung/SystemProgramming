#include <stdio.h>
#include <string.h>
#include "Write.h"
#include "Read.h"

int main() {
    char filename[100];
    char content[256];
    printf("텍스트 파일명 입력: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) return 0;
    filename[strcspn(filename, "\n")] = '\0';

    printf("파일 내용 입력: ");
    if (fgets(content, sizeof(content), stdin) == NULL) return 0;

    write_file(filename, content);
    read_file(filename);
    return 0;
}
