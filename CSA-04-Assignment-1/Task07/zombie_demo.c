/* Zombie: child exits, parent sleeps without wait(). Check with:  ps -o pid,stat,cmd --ppid <parent pid> */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void) {
    pid_t pid = fork();
    if (pid == 0) _exit(0);
    printf("parent %d, child %d exited; sleeping 10 s (child shows as Z in ps)\n", getpid(), pid);
    fflush(stdout);
    sleep(10);
    waitpid(pid, NULL, 0);
    puts("child reaped");
    return 0;
}
