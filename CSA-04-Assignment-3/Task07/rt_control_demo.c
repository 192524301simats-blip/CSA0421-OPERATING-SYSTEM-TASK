/* Real-time control skeleton: lock + pre-fault memory, FIFO priority, periodic loop with deadline check. */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sched.h>
#include <sys/mman.h>
#define PERIOD_NS 10000000L   /* 10 ms */
#define BUF (1 << 20)
static char buf[BUF];
int main(void) {
    if (mlockall(MCL_CURRENT | MCL_FUTURE) != 0) perror("mlockall (raise RLIMIT_MEMLOCK or use sudo)");
    memset(buf, 0, BUF);                                    /* pre-fault */
    struct sched_param sp = { .sched_priority = 50 };
    if (sched_setscheduler(0, SCHED_FIFO, &sp) != 0) perror("SCHED_FIFO (needs privileges; continuing)");
    struct timespec next, now; clock_gettime(CLOCK_MONOTONIC, &next);
    long worst = 0; int miss = 0;
    for (int i = 0; i < 200; i++) {
        next.tv_nsec += PERIOD_NS; if (next.tv_nsec >= 1000000000L) { next.tv_nsec -= 1000000000L; next.tv_sec++; }
        buf[i % BUF]++;                                     /* stand-in for control work */
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next, NULL);
        clock_gettime(CLOCK_MONOTONIC, &now);
        long late = (now.tv_sec - next.tv_sec) * 1000000000L + (now.tv_nsec - next.tv_nsec);
        if (late > worst) worst = late;
        if (late > 1000000L) miss++;
    }
    printf("200 cycles, worst wake-up latency %ld us, >1ms misses: %d\n", worst / 1000, miss);
    return 0;
}
