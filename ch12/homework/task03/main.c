#include <stdio.h>      // 표준 입출력 함수(printf, fgets, fprintf) 사용을 위한 헤더
#include <stdlib.h>     // 프로세스 종료(exit) 및 메모리 관련 함수 헤더
#include <unistd.h>     // 파이프, 복제, 실행 시스템 콜(pipe, fork, dup2, execvp, close) 헤더
#include <string.h>     // 문자열 분리 및 검색(strchr, strtok, strcspn) 사용을 위한 헤더
#include <sys/wait.h>   // 자식 프로세스 종료 대기(wait) 사용을 위한 헤더

#define MAXLINE 256     // 입력 명령어 줄 최대 길이 정의
#define MAXARG 32       // 각 명령어가 가질 수 있는 최대 인자 개수 정의

// 공백으로 구분된 명령어 문자열을 execvp용 인자 배열(args)로 파싱하는 함수
void parse_args(char *cmd, char **args) {
    int i = 0;                          // 인자 배열 인덱스 초기화
    char *token = strtok(cmd, " \t\n"); // 공백, 탭, 개행 기준으로 첫 번째 토큰 추출
    while (token != NULL && i < MAXARG - 1) { // 토큰이 존재하고 최대 개수 미만일 동안 반복
        args[i++] = token;              // 인자 배열에 토큰 포인터 저장
        token = strtok(NULL, " \t\n");  // 다음 토큰 추출
    }
    args[i] = NULL;                     // execvp 요구사항에 맞게 인자 배열 마지막에 NULL 설정
}

int main(int argc, char *argv[]) {
    char str[MAXLINE];                  // 입력받은 전체 명령어 라인을 저장할 버퍼
    char *cmd1, *cmd2;                  // 파이프('|') 앞과 뒤 명령어 문자열 포인터
    char *args1[MAXARG], *args2[MAXARG]; // 첫 번째 명령어와 두 번째 명령어의 인자 배열
    int fd[2];                          // 두 명령어를 연결할 파이프 파일 디스크립터 배열

    if (argc > 1) {                     // 실행 시 명령줄 인수로 직접 전달받은 경우
        str[0] = '\0';                  // 버퍼 초기화
        for (int i = 1; i < argc; i++) { // 전달받은 모든 인자를 하나의 문자열로 결합
            strcat(str, argv[i]);       // 인자 이어 붙이기
            if (i < argc - 1) strcat(str, " "); // 인자 사이 공백 추가
        }
    } else {                            // 인자 없이 실행 시 대화형 [shell] 프롬프트 출력
        printf("[shell]");              // 쉘 프롬프트 출력
        fflush(stdout);                 // 프롬프트 즉시 화면 출력
        if (fgets(str, MAXLINE, stdin) == NULL) return 0; // 사용자 명령어 입력받기
    }

    str[strcspn(str, "\n")] = '\0';     // 문자열 끝의 개행 문자('\n') 제거
    char *pipe_pos = strchr(str, '|');  // 명령어 내에서 파이프 기호('|') 위치 탐색

    if (pipe_pos != NULL) {             // 파이프 기호('|')가 포함된 경우
        *pipe_pos = '\0';               // '|' 위치를 널 문자로 바꿔 앞뒤 명령어 분리
        cmd1 = str;                     // 파이프 앞부분을 첫 번째 명령어로 지정
        cmd2 = pipe_pos + 1;            // 파이프 뒷부분을 두 번째 명령어로 지정

        parse_args(cmd1, args1);        // 첫 번째 명령어와 옵션 인자 파싱
        parse_args(cmd2, args2);        // 두 번째 명령어와 옵션 인자 파싱

        if (pipe(fd) == -1) {           // 두 명령어 연결용 이름 없는 파이프 생성
            perror("pipe");             // 파이프 생성 오류 출력
            exit(1);                    // 비정상 종료
        }

        if (fork() == 0) {              // 첫 번째 자식 프로세스 생성 (command1 실행)
            close(fd[0]);               // 첫 번째 자식은 출력만 보내므로 읽기 파이프 닫기
            dup2(fd[1], STDOUT_FILENO); // 표준 출력(1)을 파이프 쓰기 끝(fd[1])으로 재지정
            close(fd[1]);               // 복제 완료된 원본 쓰기 디스크립터 닫기
            execvp(args1[0], args1);    // command1과 해당 인자들 실행
            perror("execvp cmd1");      // execvp 실패 시 오류 메시지 출력
            exit(1);                    // 실패 시 종료
        }

        if (fork() == 0) {              // 두 번째 자식 프로세스 생성 (command2 실행)
            close(fd[1]);               // 두 번째 자식은 입력만 받으므로 쓰기 파이프 닫기
            dup2(fd[0], STDIN_FILENO);  // 표준 입력(0)을 파이프 읽기 끝(fd[0])으로 재지정
            close(fd[0]);               // 복제 완료된 원본 읽기 디스크립터 닫기
            execvp(args2[0], args2);    // command2와 해당 인자들 실행
            perror("execvp cmd2");      // execvp 실패 시 오류 메시지 출력
            exit(1);                    // 실패 시 종료
        }

        close(fd[0]);                   // 부모 프로세스의 파이프 읽기 끝 닫기
        close(fd[1]);                   // 부모 프로세스의 파이프 쓰기 끝 닫기
        wait(NULL);                     // 첫 번째 자식 프로세스 종료 대기
        wait(NULL);                     // 두 번째 자식 프로세스 종료 대기
    } else {                            // 파이프 기호가 없는 단일 명령어인 경우
        parse_args(str, args1);         // 단일 명령어와 옵션 인자 파싱
        if (args1[0] != NULL && fork() == 0) { // 자식 프로세스 생성 후 단일 명령어 실행
            execvp(args1[0], args1);    // 명령어 실행
            perror("execvp");           // 실행 실패 시 오류 출력
            exit(1);                    // 실패 시 종료
        }
        wait(NULL);                     // 자식 프로세스 종료 대기
    }

    return 0;                           // 프로그램 정상 종료 반환
}
