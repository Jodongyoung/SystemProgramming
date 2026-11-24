#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

int main(int argc, char *argv[]) {
    int fd, id;
    struct student record;

    // 1. 인자 개수 예외 처리
    if (argc < 2) {
        fprintf(stderr, "사용법 : %s 파일이름\n", argv[0]);
        exit(1);
    }

    // 2. 읽기/쓰기 모드로 파일 열기
    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    printf("수정할 학생의 학번 입력: ");
    while (scanf("%d", &id) == 1) {
        lseek(fd, 0, SEEK_SET);
        int found = 0;

        while (read(fd, (char *) &record, sizeof(record)) > 0) {
            if (record.id == id) {
                found = 1;
                // 읽은 레코드의 시작 위치로 커서 되감기
                off_t pos = lseek(fd, (off_t) -sizeof(record), SEEK_CUR);

                // 3. lockf()를 이용한 잠금 설정 (실패 시 -1 반환 예외처리)
                if (lockf(fd, F_LOCK, sizeof(record)) == -1) {
                    perror(argv[1]);
                    exit(3);
                }

                // 대기하다가 잠금이 풀렸을 때를 대비해 최신 데이터 다시 읽기
                lseek(fd, pos, SEEK_SET);
                read(fd, (char *) &record, sizeof(record));

                printf("이름: %s\n", record.name);
                printf("새로운 점수: ");
                scanf("%d", &record.score);

                // 4. 원래 레코드 위치로 이동해 수정된 점수 덮어쓰기
                lseek(fd, pos, SEEK_SET);
                write(fd, (char *) &record, sizeof(record));

                printf("학번 : %d 점수: %d\n", record.id, record.score);

                // 5. 잠금 해제 (F_ULOCK)
                lseek(fd, pos, SEEK_SET);
                lockf(fd, F_ULOCK, sizeof(record));
                break;
            }
        }

        if (!found) {
            printf("레코드 %d 없음\n", id);
        }

        printf("\n수정할 학생의 학번 입력: ");
    }

    close(fd);
    return 0;
}