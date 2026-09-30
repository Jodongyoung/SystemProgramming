#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

int main(int argc, char *argv[]) {
    int fd;
    struct student record;

    if (argc < 2) {
        fprintf(stderr, "사용법: %s file\n", argv[0]);
        exit(1);
    }

    // 쓰기 모드(O_WRONLY), 생성(O_CREAT), 내용비우기(O_TRUNC), 권한 0640
    if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0640)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    printf("%-9s %-8s %-4s\n", "학번", "이름", "점수");

    // 슬라이드 16페이지: 학번, 이름, 점수를 입력받아 오프셋 위치에 저장
    while (scanf("%d %s %d", &record.id, record.name, &record.score) == 3) {
        lseek(fd, (off_t)(record.id - START_ID) * sizeof(record), SEEK_SET);
        write(fd, (char *)&record, sizeof(record));
    }

    close(fd);
    exit(0);
}
