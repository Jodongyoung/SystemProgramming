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

    // 1. 읽기 모드(O_RDONLY)로 파일 열기
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    // 2. do-while을 이용한 반복 학번 검색
    do {
        printf("검색할 학생의 학번 입력: ");
        if (scanf("%d", &id) == 1) {
            // lseek으로 해당 학번 레코드 위치로 순간이동
            lseek(fd, (off_t)(id - START_ID) * sizeof(record), SEEK_SET);

            // read로 1명 레코드 분량을 읽어오고 학번 유효성 확인
            if ((read(fd, (char *)&record, sizeof(record)) > 0) && (record.id != 0)) {
                printf("이름: %s\t 학번 : %d\t 점수: %d\n", record.name, record.id, record.score);
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
