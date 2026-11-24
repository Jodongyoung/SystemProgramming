#include <stdio.h>      // 표준 입출력 함수(printf, sprintf) 사용을 위한 헤더
#include <stdlib.h>     // 프로세스 종료 함수(exit) 사용을 위한 헤더
#include <unistd.h>     // 파이프 및 프로세스 제어(pipe, fork, read, write, close, getpid) 헤더
#include <string.h>     // 문자열 길이 계산(strlen) 사용을 위한 헤더
#include <sys/wait.h>   // 자식 프로세스 종료 대기(wait) 사용을 위한 헤더

#define MAXLINE 100     // 파이프로 주고받을 버퍼 최대 크기 정의

int main() {
    int n, length, fd[2], pid;          // 읽은 바이트 수(n), 문자열 길이, 파이프 디스크립터 배열(fd), 프로세스 ID 변수
    char message[MAXLINE], line[MAXLINE]; // 송신용 버퍼(message)와 수신용 버퍼(line) 선언

    pipe(fd);                           // 이름 없는 파이프 생성 (fd[0]: 읽기용, fd[1]: 쓰기용)

    if ((pid = fork()) == 0) {          // 자식 프로세스 생성 및 자식 영역 분기
        close(fd[0]);                   // 자식은 쓰기만 수행하므로 읽기용 파이프 닫기
        sprintf(message, "Hello from PID %d\n", getpid()); // 자식 PID가 포함된 문자열 생성
        length = strlen(message) + 1;   // 널 종료 문자를 포함한 문자열 전체 길이 계산
        printf("Send: [%d] %s", getpid(), message); // 자식이 보낼 메시지와 자신의 PID 출력
        write(fd[1], message, length);  // 쓰기용 파이프(fd[1])를 통해 부모에게 문자열 전송
        close(fd[1]);                   // 데이터 전송 완료 후 쓰기용 파이프 닫기
        exit(0);                        // 자식 프로세스 정상 종료
    } else {                            // 부모 프로세스 영역 분기
        close(fd[1]);                   // 부모는 읽기만 수행하므로 쓰기용 파이프 닫기
        n = read(fd[0], line, MAXLINE); // 읽기용 파이프(fd[0])로부터 자식이 보낸 데이터 수신
        printf("Recv: [%d] %s", getpid(), line); // 부모의 PID와 수신받은 메시지 출력
        close(fd[0]);                   // 데이터 수신 완료 후 읽기용 파이프 닫기
        wait(NULL);                     // 자식 프로세스가 완전히 종료될 때까지 대기
    }

    return 0;                           // 프로그램 정상 종료 반환
}
