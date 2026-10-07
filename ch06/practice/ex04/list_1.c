#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    DIR *dp;
    char *dir;
    struct dirent *d;

    // 인자가 전달되지 않으면 현재 디렉터리(.), 있으면 해당 인자 경로 사용
    if (argc == 1)
        dir = ".";
    else
        dir = argv[1];

    // 1. 디렉터리 열기 및 예외 처리 (접근 불가 시 에러 출력 후 종료)
    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }

    // 2. while 반복문과 readdir()로 파일 이름들을 한 줄씩 출력
    while ((d = readdir(dp)) != NULL) {
        printf("%s\n", d->d_name);
    }

    // 3. 디렉터리 닫기
    closedir(dp);
    exit(0);
}
