#include <stdio.h>      // 표준 입출력 함수(printf) 사용을 위한 헤더
#include <stdlib.h>     // 프로세스 종료 함수(exit) 사용을 위한 헤더
#include <unistd.h>     // 알람 및 대기 함수(alarm, sleep) 사용을 위한 헤더
#include <signal.h>     // 시그널 및 sigaction 구조체 사용을 위한 헤더

// 시그널 핸들러 함수 포인터 타입 정의
typedef void (*sighandler_t)(int);

// sigaction() 시스템을 이용해 사용자 정의 signal() 함수 구현
sighandler_t signal(int signo, sighandler_t func) {
    struct sigaction act, oact;             // 새 시그널 액션(act)과 기존 액션(oact) 구조체 선언
    act.sa_handler = func;                  // 시그널 발생 시 호출할 핸들러 함수 지정
    sigemptyset(&act.sa_mask);              // 핸들러 실행 중 블록할 추가 시그널 집합 비우기
    act.sa_flags = 0;                       // 특수 옵션 플래그 0으로 초기화

    if (sigaction(signo, &act, &oact) < 0)  // 커널에 시그널 처리기 등록 및 오류 확인
        return SIG_ERR;                     // 등록 실패 시 SIG_ERR 반환

    return oact.sa_handler;                 // 등록 성공 시 기존에 설정되어 있던 핸들러 반환
}

// SIGALRM 시그널 발생 시 실행될 핸들러 함수
void alarmHandler(int signo) {
    printf("일어나세요\n");                  // 알람 도착 메시지 출력
    exit(0);                                // 프로세스 정상 종료
}

int main() {
    int i = 0;                              // 경과 시간을 셀 카운터 변수 초기화
    signal(SIGALRM, alarmHandler);          // 직접 구현한 signal()로 SIGALRM 핸들러 등록
    alarm(5);                               // 5초 뒤에 SIGALRM 시그널이 발생하도록 타이머 설정
    printf("무한 루프\n");                   // 루프 진입 안내 문구 출력

    while (1) {                             // 시그널이 발생할 때까지 무한 반복
        sleep(1);                           // 1초간 프로세스 대기
        i++;                                // 경과 시간 1초 증가
        printf("%d초 경과\n", i);           // 현재까지 경과한 초 출력
    }

    return 0;                               // 프로그램 종료 반환값
}
