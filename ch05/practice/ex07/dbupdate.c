#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

int main(int argc, char *argv[]) {
    int fd, id;
    char c;
    struct student record;

    if (argc < 2) {
        fprintf(stderr, "사용법: %s file\n", argv[0]);
        exit(1);
    }

    // 1. 읽기와 쓰기가 모두 가능해야 하므로 O_RDWR로 열기
    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    do {
        printf("수정할 학생의 학번 입력: ");
        if (scanf("%d", &id) == 1) {
            // 해당 학번의 시작 위치로 이동
            lseek(fd, (off_t)(id - START_ID) * sizeof(record), SEEK_SET);

            if ((read(fd, (char *)&record, sizeof(record)) > 0) && (record.id != 0)) {
                printf("학번: %8d 이름: %4s 점수: %4d\n", record.id, record.name, record.score);
                printf("새로운 점수 입력: ");
                scanf("%d", &record.score);

                // 핵심: read로 인해 앞으로 이동한 포인터를 다시 1명 크기만큼 뒤로 되감기
                lseek(fd, (off_t)-sizeof(record), SEEK_CUR);

                // 새로운 점수가 반영된 레코드로 덮어쓰기
                write(fd, (char *)&record, sizeof(record));
            } else {
                printf("레코드 %d 없음\n", id);
            }
        } else {
            printf("입력 오류\n");
        }

        printf("계속하겠습니까?(Y/N)");
        scanf(" %c", &c);
    } while (c == 'Y' || c == 'y');

    close(fd);
    exit(0);
}
