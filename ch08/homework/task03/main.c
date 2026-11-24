#include <stdio.h>
#include <unistd.h>

int main() {
    int pid;
    printf("[1] = %d\n", getpid());
    if ((pid = fork()) == 0)
        printf("[2] = %d %d \n", getpid(), getppid());
    sleep(1);
    return 0;
}
