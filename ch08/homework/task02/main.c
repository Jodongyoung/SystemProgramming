#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("my process number: [%d]\n", getpid());
    printf("my parent's process number: [%d]\n", getppid());
    system("ps");
    return 0;
}
