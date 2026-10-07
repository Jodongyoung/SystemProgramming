#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

// 파일 정보 출력 함수 (옵션 반영)
void printStat(char *file, struct stat *st, int opt_i, int opt_p, int opt_Q) {
    char mode[11] = "----------";

    // 1. 파일 종류 판별
    if (S_ISDIR(st->st_mode)) mode[0] = 'd';
    else if (S_ISCHR(st->st_mode)) mode[0] = 'c';
    else if (S_ISBLK(st->st_mode)) mode[0] = 'b';
    else if (S_ISLNK(st->st_mode)) mode[0] = 'l';
    else if (S_ISFIFO(st->st_mode)) mode[0] = 'p';
    else if (S_ISSOCK(st->st_mode)) mode[0] = 's';

    // 2. 접근 권한 비트 판별
    if (st->st_mode & S_IRUSR) mode[1] = 'r';
    if (st->st_mode & S_IWUSR) mode[2] = 'w';
    if (st->st_mode & S_IXUSR) mode[3] = 'x';
    if (st->st_mode & S_IRGRP) mode[4] = 'r';
    if (st->st_mode & S_IWGRP) mode[5] = 'w';
    if (st->st_mode & S_IXGRP) mode[6] = 'x';
    if (st->st_mode & S_IROTH) mode[7] = 'r';
    if (st->st_mode & S_IWOTH) mode[8] = 'w';
    if (st->st_mode & S_IXOTH) mode[9] = 'x';

    // 3. 소유자 및 그룹 이름 획득
    struct passwd *pw = getpwuid(st->st_uid);
    struct group *gr = getgrgid(st->st_gid);

    // 4. -p, -Q 옵션에 따른 파일명 가공
    char namebuf[512];
    char tempname[512];
    strcpy(tempname, file);

    // -p 옵션: 디렉터리일 경우 뒤에 '/' 추가
    if (opt_p && S_ISDIR(st->st_mode)) {
        strcat(tempname, "/");
    }

    // -Q 옵션: 파일명을 큰따옴표로 감쌈
    if (opt_Q) {
        snprintf(namebuf, sizeof(namebuf), "\"%s\"", tempname);
    } else {
        strcpy(namebuf, tempname);
    }

    // 5. 출력 형식 맞추기
    // 블록 크기 출력
    printf("%2ld ", (long)st->st_blocks);

    // -i 옵션: i-노드 번호 출력
    if (opt_i) {
        printf("%ld ", (long)st->st_ino);
    }

    // 나머지 상세 정보(권한, 링크수, 소유자, 그룹, 파일크기, 시간, 파일명) 출력
    printf("%s %2ld %s %s %8ld %.12s %s\n",
           mode,
           (long)st->st_nlink,
           pw ? pw->pw_name : "unknown",
           gr ? gr->gr_name : "unknown",
           (long)st->st_size,
           ctime(&st->st_mtime) + 4,
           namebuf);
}

int main(int argc, char *argv[]) {
    int opt;
    int opt_i = 0, opt_p = 0, opt_Q = 0;

    // getopt 함수로 -i, -p, -Q 옵션 파싱
    while ((opt = getopt(argc, argv, "ipQ")) != -1) {
        switch (opt) {
            case 'i': opt_i = 1; break;
            case 'p': opt_p = 1; break;
            case 'Q': opt_Q = 1; break;
            default:
                fprintf(stderr, "사용법: %s [-i] [-p] [-Q] [디렉터리]\n", argv[0]);
                exit(1);
        }
    }

    // 대상 디렉터리 지정 (기본값은 현재 디렉터리 ".")
    char *dir = ".";
    if (optind < argc) {
        dir = argv[optind];
    }

    DIR *dp = opendir(dir);
    if (dp == NULL) {
        perror(dir);
        exit(1);
    }

    struct dirent *d;
    struct stat st;
    char path[1024];

    // 디렉터리 내의 모든 파일 항목 순회
    while ((d = readdir(dp)) != NULL) {
        snprintf(path, sizeof(path), "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0) {
            perror(path);
            continue;
        }
        printStat(d->d_name, &st, opt_i, opt_p, opt_Q);
    }

    closedir(dp);
    return 0;
}
