/* Demand paging: count page faults while touching pages, then show copy-on-write after fork. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/wait.h>
static void faults(long *mi, long *ma) {
    struct rusage r; getrusage(RUSAGE_SELF, &r); *mi = r.ru_minflt; *ma = r.ru_majflt;
}
int main(int argc, char **argv) {
    size_t mb = argc > 1 ? (size_t)atoi(argv[1]) : 64;     /* keep small; do not exhaust host */
    long ps = sysconf(_SC_PAGESIZE);
    size_t len = mb << 20, pages = len / ps;
    char *p = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (p == MAP_FAILED) { perror("mmap"); return 1; }
    long mi0, ma0, mi1, ma1; faults(&mi0, &ma0);
    for (size_t i = 0; i < pages; i++) p[i * ps] = 1;       /* one byte per page */
    faults(&mi1, &ma1);
    printf("page size %ld, mapped %zu MiB (%zu pages)\n", ps, mb, pages);
    printf("minor faults +%ld, major faults +%ld\n", mi1 - mi0, ma1 - ma0);

    puts("\n== Copy-on-write after fork ==");
    p[0] = 'A';
    fflush(stdout);
    pid_t pid = fork();
    if (pid == 0) {
        long a, b, c, d; faults(&a, &b);
        p[0] = 'B';                                          /* write triggers COW copy */
        faults(&c, &d);
        printf("child : p[0]='%c', extra minor faults on first write = %ld\n", p[0], c - a);
        fflush(stdout);
        _exit(0);
    }
    wait(NULL);
    printf("parent: p[0]='%c' (unchanged by child)\n", p[0]);
    munmap(p, len);
    return 0;
}
