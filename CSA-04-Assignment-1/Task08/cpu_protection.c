/* Task 8: (1) privileged instruction in user mode is trapped; (2) timer interrupt (SIGALRM)
   regains control from a busy loop; (3) polling-interval worst-case detection delay. */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
static volatile sig_atomic_t ticks = 0;
static void on_tick(int s) { (void)s; ticks++; }
int main(void) {
    puts("== 1. Privileged instruction in user mode ==");
    fflush(stdout);
    pid_t pid = fork();
    if (pid == 0) {
#if defined(__x86_64__) || defined(__i386__)
        __asm__ volatile("cli");               /* disable interrupts: privileged */
#endif
        _exit(0);
    }
    int st; waitpid(pid, &st, 0);
    if (WIFSIGNALED(st)) printf("child killed by signal %d (SIGSEGV=11): CPU trapped the privileged instruction\n", WTERMSIG(st));
    else puts("child exited normally (non-x86 build: instruction not tried)");

    puts("\n== 2. Timer interrupt breaks a busy loop ==");
    struct sigaction sa; sa.sa_handler = on_tick; sigemptyset(&sa.sa_mask); sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);
    struct itimerval it = {{0, 100000}, {0, 100000}};  /* every 100 ms */
    setitimer(ITIMER_REAL, &it, NULL);
    while (ticks < 5) { }                               /* spins; handler runs asynchronously */
    puts("busy loop interrupted 5 times by the timer");

    puts("\n== 3. Polling worst-case detection delay ~ P + processing ==");
    int periods[] = {1, 5, 10, 20};
    for (int i = 0; i < 4; i++)
        printf("poll every %2d ms -> worst wait %2d ms + processing: %s the 10 ms deadline\n",
               periods[i], periods[i], periods[i] < 10 ? "can meet" : "cannot meet");
    return 0;
}
