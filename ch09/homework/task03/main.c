#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAXLINE 1024
#define MAXARG 64

void execute_single_cmd(char *cmd) {
    char *args[MAXARG];
    int background = 0;
    char *infile = NULL, *outfile = NULL;

    char *p = cmd;
    while (*p == ' ' || *p == '\t') p++;
    if (*p == '\0') return;

    int len = strlen(p);
    while (len > 0 && (p[len - 1] == ' ' || p[len - 1] == '\t' || p[len - 1] == '\n')) len--;
    p[len] = '\0';
    if (len > 0 && p[len - 1] == '&') {
        background = 1;
        p[len - 1] = '\0';
    }

    int i = 0;
    char *token = strtok(p, " \t\n");
    while (token != NULL) {
        if (strcmp(token, ">") == 0) {
            outfile = strtok(NULL, " \t\n");
        } else if (strcmp(token, "<") == 0) {
            infile = strtok(NULL, " \t\n");
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
    if (args[0] == NULL) return;

    if (strcmp(args[0], "exit") == 0) exit(0);

    pid_t pid = fork();
    if (pid == 0) {
        if (outfile) {
            int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
            if (fd < 0) { perror("open output"); exit(1); }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        if (infile) {
            int fd = open(infile, O_RDONLY);
            if (fd < 0) { perror("open input"); exit(1); }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        execvp(args[0], args);
        fprintf(stderr, "%s: command not found\n", args[0]);
        exit(1);
    } else if (pid > 0) {
        if (!background) {
            waitpid(pid, NULL, 0);
        } else {
            printf("[Process running in background, PID: %d]\n", pid);
        }
    }
}

int main() {
    char line[MAXLINE];
    while (1) {
        printf("[shell] ");
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin)) break;
        if (strcmp(line, "\n") == 0) continue;

        char *saveptr;
        char *cmd = strtok_r(line, ";\n", &saveptr);
        while (cmd != NULL) {
            execute_single_cmd(cmd);
            cmd = strtok_r(NULL, ";\n", &saveptr);
        }
    }
    return 0;
}
