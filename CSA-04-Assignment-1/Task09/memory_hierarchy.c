/* Task 9: measure (on YOUR machine) access latency vs working-set size via pointer chasing,
   and compute the interrupt-per-word vs DMA comparison. Results are machine-dependent. */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
static double now(void) { struct timespec t; clock_gettime(CLOCK_MONOTONIC, &t); return t.tv_sec + t.tv_nsec / 1e9; }
int main(void) {
    puts("working_set_KiB,ns_per_access   (measured here)");
    for (size_t kib = 16; kib <= 65536; kib *= 4) {
        size_t n = kib * 1024 / sizeof(size_t);
        size_t *a = malloc(n * sizeof *a);
        size_t *perm = malloc(n * sizeof *perm);
        if (!a || !perm) return 1;
        for (size_t i = 0; i < n; i++) perm[i] = i;
        srand(1);
        for (size_t i = n - 1; i > 0; i--) { size_t j = (size_t)rand() % (i + 1); size_t t = perm[i]; perm[i] = perm[j]; perm[j] = t; }
        for (size_t i = 0; i < n; i++) a[perm[i]] = perm[(i + 1) % n];   /* one random cycle */
        size_t p = perm[0]; long steps = 20000000;
        double t0 = now();
        for (long i = 0; i < steps; i++) p = a[p];
        double t1 = now();
        printf("%zu,%.2f%s\n", kib, (t1 - t0) / steps * 1e9, p == (size_t)-1 ? "!" : "");
        free(a); free(perm);
    }
    puts("\n== 500 MB transfer, 4-byte words ==");
    printf("decimal 500 MB : %.0f interrupts if one per word\n", 500e6 / 4);
    printf("500 MiB        : %.0f interrupts if one per word\n", 500.0 * 1048576 / 4);
    printf("DMA, 1 MiB blocks: %.0f completion interrupts\n", 500e6 / 1048576);
    return 0;
}
