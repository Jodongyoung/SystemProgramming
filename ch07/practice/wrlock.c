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
                off_t pos = lseek(fd, (off_t) -sizeof(record), SEEK_CUR);

                // 쓰기 잠금 설정 (F_WRLCK - 독점)
                lock.l_type = F_WRLCK;
                lock.l_whence = SEEK_SET;
                lock.l_start = pos;
                lock.l_len = sizeof(record);

                // F_SETLKW를 사용하여 잠금을 획득할 때까지 대기(블로킹)
                if (fcntl(fd, F_SETLKW, &lock) == -1) {
                    perror("fcntl lock");
                    exit(3);
                }

                printf("이름: %s\n", record.name);
                printf("현재 점수: %d\n", record.score);
                printf("새로운 점수 입력 (수정 완료하려면 엔터 및 대기): ");
                scanf("%d", &record.score);

                // 수정된 데이터 덮어쓰기
                lseek(fd, pos, SEEK_SET);
                write(fd, (char *) &record, sizeof(record));

                printf("학번 : %d 점수: %d 수정 완료!\n", record.id, record.score);
                printf("--- [주의] 현재 쓰기 잠금 유지 중입니다. 다른 터미널에서 rdlock을 실행해 보세요. ---\n");

                // 테스트를 위해 엔터를 한 번 더 입력받아 잠금을 유지하도록 대기시킴
                printf("잠금을 풀려면 엔터 키를 누르세요...");
                getchar(); // 버퍼 비우기용
                getchar(); // 엔터 대기

                // 잠금 해제
                lock.l_type = F_UNLCK;
                fcntl(fd, F_SETLK, &lock);
                printf("쓰기 잠금이 해제되었습니다.\n");
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