/* Segmentation: segment table with base/limit, tests, and a fragmentation simulation. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
typedef struct { unsigned base, limit; } Seg;
static int translate(const Seg *t, int nseg, int s, unsigned d, unsigned *pa) {
    if (s < 0 || s >= nseg) return -1;
    if (d >= t[s].limit) return -1;           /* 0 <= d < limit */
    *pa = t[s].base + d; return 0;
}
static void test_access(const Seg *t, int n, int s, unsigned d) {
    fflush(stdout);
    pid_t pid = fork();                        /* isolate invalid access in a child */
    if (pid == 0) {
        unsigned pa;
        if (translate(t, n, s, d, &pa) == 0) { printf("(seg %2d, off %4u) -> PA %u  OK\n", s, d, pa); exit(0); }
        printf("(seg %2d, off %4u) -> TRAP: protection fault\n", s, d); exit(2);
    }
    int st; waitpid(pid, &st, 0);
}
#define UNITS 10000
#define NSEGS 20
int main(void) {
    Seg t[4] = {{1000, 400}, {6300, 400}, {4300, 1100}, {3200, 1000}};
    puts("== Segment translation tests ==");
    int cases[][2] = {{0,0},{0,399},{0,400},{1,100},{2,1099},{2,1100},{3,500},{4,0},{-1,5}};
    for (unsigned i = 0; i < sizeof cases / sizeof cases[0]; i++)
        test_access(t, 4, cases[i][0], (unsigned)cases[i][1]);

    puts("\n== Fragmentation simulation (seed 42) ==");
    srand(42);
    static char mem[UNITS];
    int start[NSEGS], size[NSEGS], placed[NSEGS] = {0};
    for (int i = 0; i < NSEGS; i++) {
        size[i] = 100 + rand() % 700;
        for (int pos = 0; pos + size[i] <= UNITS; pos++) {   /* first fit */
            int ok = 1;
            for (int k = 0; k < size[i]; k++) if (mem[pos + k]) { ok = 0; pos += k; break; }
            if (ok) { start[i] = pos; placed[i] = 1; for (int k = 0; k < size[i]; k++) mem[pos+k] = 1; break; }
        }
    }
    for (int i = 0; i < NSEGS; i += 3)
        if (placed[i]) for (int k = 0; k < size[i]; k++) mem[start[i] + k] = 0;
    int free_u = 0, largest = 0, run = 0;
    for (int i = 0; i < UNITS; i++) {
        if (!mem[i]) { free_u++; run++; if (run > largest) largest = run; } else run = 0;
    }
    printf("free units: %d, largest hole: %d, fragmentation = 1 - largest/free = %.4f\n",
           free_u, largest, free_u ? 1.0 - (double)largest / free_u : 0.0);
    return 0;
}
