#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXARG 64
#define MAXLINE 1024

int main() {
    char line[MAXLINE];
    char *args[MAXARG];
    int pid, child, status;

    while (1) {
        printf("Pls input cmd : ");
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin)) break;

        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) == 0) continue;

        printf("[%d] Parent process start\n", getpid());

        int background = 0;
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '&') {
            background = 1;
            line[len - 1] = '\0';
        }

        int i = 0;
        char *saveptr;
        char *token = strtok_r(line, " \t", &saveptr);
        while (token != NULL && i < MAXARG - 1) {
            args[i++] = token;
            token = strtok_r(NULL, " \t", &saveptr);
        }
        args[i] = NULL;

        if (args[0] == NULL) continue;
        if (strcmp(args[0], "exit") == 0) break;

        pid = fork();
        if (pid == 0) {
            if (background) {
                printf("[%d] child process start\n", getpid());
            }
            execvp(args[0], &args[0]);
            printf("Parent process end\n");
            printf("Exit\n");
            exit(1);
        } else if (pid > 0) {
            child = wait(&status);
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                if (background) {
                    printf("[%d] child process end %d\n", getpid(), child);
                }
                printf("SUCCESS\n");
            }
        }
    }
    return 0;
}
