#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

extern char **environ;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s [-e [env_name] | -u | -g | -i | -p]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-e") == 0) {
        if (argc == 2) {
            printf("-e EMPTY\n");
            char **ptr;
            for (ptr = environ; *ptr != 0; ptr++) {
                printf("%s\n", *ptr);
            }
        } else {
            printf("-e %s\n", argv[2]);
            char *val = getenv(argv[2]);
            if (val != NULL) {
                printf("%s = %s\n", argv[2], val);
            } else {
                printf("%s is not found\n", argv[2]);
            }
        }
    }
    else if (strcmp(argv[1], "-u") == 0) {
        printf("-u EMPTY\n");
        printf("My Realistic User ID: %d(%s)\n", getuid(), getpwuid(getuid())->pw_name);
        printf("My Valid User ID: %d(%s)\n", geteuid(), getpwuid(geteuid())->pw_name);
    }
    else if (strcmp(argv[1], "-g") == 0) {
        printf("-g EMPTY\n");
        printf("My Realistic Group ID: %d(%s)\n", getgid(), getgrgid(getgid())->gr_name);
        printf("My Valid Group ID: %d(%s)\n", getegid(), getgrgid(getegid())->gr_name);
    }
    else if (strcmp(argv[1], "-i") == 0) {
        printf("-i EMPTY\n");
        printf("my process number : [%d]\n", getpid());
    }
    else if (strcmp(argv[1], "-p") == 0) {
        printf("-p EMPTY\n");
        printf("my parent's process number : [%d]\n", getppid());
    }
    else {
        printf("Unknown option: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
