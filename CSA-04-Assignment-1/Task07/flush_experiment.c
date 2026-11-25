/* Shows why stdout must be flushed before fork() when output is redirected.
   Run:  ./flush_experiment > out.txt ; cat out.txt   (duplicate line appears) */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void) {
    printf("shell: running job 2\n");          /* NO fflush on purpose */
    pid_t pid = fork();
    if (pid == 0) exit(3);                     /* exit() flushes the inherited buffer; _exit(3) would not */
    int st; waitpid(pid, &st, 0);
    printf("job 2 exit status %d\n", WEXITSTATUS(st));
    return 0;
}
