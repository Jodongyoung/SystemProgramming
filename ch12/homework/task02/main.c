#include <stdio.h>      // 표준 입출력 함수(printf, fgets, fflush) 사용을 위한 헤더
#include <stdlib.h>     // 프로세스 종료 함수(exit) 사용을 위한 헤더
#include <unistd.h>     // 파이프 및 프로세스 생성(pipe, fork, read, write, close) 헤더
#include <string.h>     // 문자열 길이 계산(strlen) 사용을 위한 헤더
#include <ctype.h>      // 문자 대문자 변환 함수(toupper) 사용을 위한 헤더
#include <sys/wait.h>   // 자식 프로세스 종료 대기(wait) 사용을 위한 헤더

#define MAXLINE 256     // 입력 및 파이프 통신용 버퍼 크기 정의

int main() {
    int fd[2];                          // 두 자식 프로세스 간 통신을 위한 파이프 배열 선언
    pid_t pid1, pid2;                   // 첫 번째 자식과 두 번째 자식의 프로세스 ID 저장 변수

    printf("parent process start\n");   // 부모 프로세스 시작 안내 메시지 출력
    fflush(stdout);                     // fork() 전 출력 버퍼가 중복 출력되지 않도록 비우기

    if (pipe(fd) == -1) {               // 이름 없는 파이프 생성 및 실패 여부 확인
        perror("pipe");                 // 파이프 생성 실패 시 오류 출력
        exit(1);                        // 비정상 종료
    }

    if ((pid1 = fork()) == 0) {         // 첫 번째 자식 프로세스 생성 (키보드 입력 담당)
        char buf[MAXLINE];              // 키보드 입력 문자열을 담을 버퍼 선언
        close(fd[0]);                   // 첫 번째 자식은 쓰기만 하므로 읽기용 파이프 닫기
        printf("input string: ");       // 사용자에게 문자열 입력 프롬프트 출력
        fflush(stdout);                 // 프롬프트 즉시 화면 출력
        if (fgets(buf, MAXLINE, stdin) != NULL) { // 키보드로부터 한 줄 문자열 입력받기
            write(fd[1], buf, strlen(buf) + 1);   // 입력받은 문자열을 파이프 쓰기 끝(fd[1])으로 전송
        }
        close(fd[1]);                   // 전송 완료 후 쓰기용 파이프 닫기
        exit(0);                        // 첫 번째 자식 프로세스 종료
    }

    if ((pid2 = fork()) == 0) {         // 두 번째 자식 프로세스 생성 (대문자 변환 및 출력 담당)
        char buf[MAXLINE];              // 파이프로부터 읽은 문자열을 담을 버퍼 선언
        close(fd[1]);                   // 두 번째 자식은 읽기만 하므로 쓰기용 파이프 닫기
        int n = read(fd[0], buf, MAXLINE); // 첫 번째 자식이 보낸 문자열을 파이프에서 읽기
        if (n > 0) {                    // 정상적으로 데이터를 읽었을 경우
            for (int i = 0; buf[i] != '\0'; i++) { // 문자열 끝까지 한 글자씩 순회
                buf[i] = toupper((unsigned char)buf[i]); // 소문자를 대문자로 변환
            }
            printf("%s", buf);          // 대문자로 변환된 최종 문자열 출력
        }
        close(fd[0]);                   // 읽기 완료 후 읽기용 파이프 닫기
        exit(0);                        // 두 번째 자식 프로세스 종료
    }

    close(fd[0]);                       // 부모 프로세스는 파이프를 직접 쓰지 않으므로 읽기 끝 닫기
    close(fd[1]);                       // 부모 프로세스 쓰기 끝 닫기 (닫아야 EOF 전달 가능)
    wait(NULL);                         // 첫 번째 자식 프로세스 종료 대기
    wait(NULL);                         // 두 번째 자식 프로세스 종료 대기

    return 0;                           // 부모 프로세스 정상 종료 반환
}
