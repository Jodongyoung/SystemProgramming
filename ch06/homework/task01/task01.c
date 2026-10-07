#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    printf("========================================\n");
    printf("[1] ls -sl test.txt (블록 수 및 권한 확인)\n");
    printf("========================================\n");
    system("touch test.txt && ls -sl test.txt");

    printf("\n========================================\n");
    printf("[2] stat test.txt (i-노드 전체 상세 정보)\n");
    printf("========================================\n");
    system("stat test.txt");

    printf("\n========================================\n");
    printf("[3] ls -i test.txt (i-노드 번호 확인)\n");
    printf("========================================\n");
    system("ls -i test.txt");

    printf("\n========================================\n");
    printf("[4] touch 전후 시간 변경 비교\n");
    printf("========================================\n");
    printf("변경 전 시간:\n");
    system("ls -al test.txt");
    sleep(2);
    system("touch test.txt");
    printf("touch 실행 후 갱신된 시간:\n");
    system("ls -al test.txt");
    printf("========================================\n");

    return 0;
}
