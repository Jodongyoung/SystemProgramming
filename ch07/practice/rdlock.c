#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

int main(int argc, char *argv[]) {
    int fd, id;
    struct student record;
    struct flock lock;

    // 예외처리: 인자가 부족할 때 종료
    if (argc < 2) {
        fprintf(stderr, "사용법 : %s 파일이름\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    printf("검색할 학생의 학번 입력: ");
    while (scanf("%d", &id) == 1) {
        lseek(fd, 0, SEEK_SET);
        int found = 0;

        while (read(fd, (char *) &record, sizeof(record)) > 0) {
            if (record.id == id) {
                found = 1;
                off_t pos = lseek(fd, (off_t) -sizeof(record), SEEK_CUR);

                // 읽기 잠금 설정 (F_RDLCK - 공유)
                lock.l_type = F_RDLCK;
                lock.l_whence = SEEK_SET;
                lock.l_start = pos;
                lock.l_len = sizeof(record);

                printf("읽기 잠금 시도 중 (다른 프로세스가 쓰기 중이면 대기합니다)...\n");

                // F_SETLKW: 쓰기 잠금이 걸려있으면 풀릴 때까지 여기서 멈춰서(블로킹) 대기함
                if (fcntl(fd, F_SETLKW, &lock) == -1) {
                    perror("fcntl lock");
                    exit(3);
                }

                // 잠금 획득 후 정보 출력
                printf("학번: %d 이름: %s 점수: %d\n", record.id, record.name, record.score);

                // 잠금 해제
                lock.l_type = F_UNLCK;
                fcntl(fd, F_SETLK, &lock);
                break;
            }
        }

        if (!found) {
            printf("레코드 %d 없음\n", id);
        }

        printf("\n검색할 학생의 학번 입력: ");
    }

    close(fd);
    return 0;
}