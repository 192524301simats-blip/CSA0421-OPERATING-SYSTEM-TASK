/* Disk scheduling: six static algorithms + seeded FCFS/SSTF event simulation (SIMULATED values). */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXQ 16
static int cmp(const void *a, const void *b) { return *(const int *)a - *(const int *)b; }
static int fcfs(int h, const int *q, int n) { int t = 0; for (int i = 0; i < n; i++) { t += abs(q[i]-h); h = q[i]; } return t; }
static int sstf(int h, const int *q, int n, int *order) {
    int done[MAXQ] = {0}, t = 0;
    for (int k = 0; k < n; k++) {
        int b = -1;
        for (int i = 0; i < n; i++) if (!done[i] && (b < 0 || abs(q[i]-h) < abs(q[b]-h))) b = i;
        done[b] = 1; t += abs(q[b]-h); h = q[b]; order[k] = h;
    } return t;
}
static int scan_down(int h, const int *q, int n) { /* toward 0 first, include cylinder 0 */
    int hi = 0; for (int i = 0; i < n; i++) if (q[i] > hi) hi = q[i];
    return h + (hi > h ? hi : h);
}
static int cscan_up(int h, const int *q, int n, int max) { /* up to max, wrap to 0, up to largest below head */
    int lo = -1; for (int i = 0; i < n; i++) if (q[i] < h && q[i] > lo) lo = q[i];
    return (max - h) + max + (lo > 0 ? lo : 0);
}
static int look_down(int h, const int *q, int n) {
    int lo = 1 << 30, hi = -1;
    for (int i = 0; i < n; i++) { if (q[i] < lo) lo = q[i]; if (q[i] > hi) hi = q[i]; }
    return (h - lo) + (hi > h ? hi - lo : 0);
}
static int clook_up(int h, const int *q, int n) {
    int s[MAXQ]; for (int i = 0; i < n; i++) s[i] = q[i];
    qsort(s, n, sizeof(int), cmp);
    int hi = s[n-1], lo = s[0], below = -1;
    for (int i = 0; i < n; i++) if (s[i] < h) below = s[i];
    int t = hi > h ? hi - h : 0;
    if (below >= 0) t += (hi - lo) + (below - lo);   /* jump back + sweep up to largest below head */
    return t;
}
/* ---- event simulation ---- */
#define REQ 10000
#define CYL 200
static double urand(void) { return (rand() + 1.0) / (RAND_MAX + 2.0); }
static double simulate(int use_sstf, double mean_gap_ms, unsigned seed) {
    srand(seed);
    static double arr[REQ]; static int cyl[REQ];
    double t = 0;
    for (int i = 0; i < REQ; i++) { t += -mean_gap_ms * log(urand()); arr[i] = t; cyl[i] = rand() % CYL; }
    double now = 0, wait_sum = 0; int head = 100, served = 0, next = 0;
    int pend[REQ], np = 0;
    while (served < REQ) {
        while (next < REQ && arr[next] <= now) pend[np++] = next++;
        if (np == 0) { now = arr[next]; continue; }
        int pick = 0;
        if (use_sstf) { for (int i = 1; i < np; i++) if (abs(cyl[pend[i]]-head) < abs(cyl[pend[pick]]-head)) pick = i; }
        int r = pend[pick]; pend[pick] = pend[--np];
        if (!use_sstf) { /* FCFS: oldest pending is lowest index */
            int m = 0; pend[np] = r; for (int i = 0; i <= np; i++) if (pend[i] < pend[m]) m = i;
            r = pend[m]; pend[m] = pend[np]; }
        double svc = 4.0 + 0.05 * abs(cyl[r]-head);           /* ms: rotation+transfer + seek model */
        wait_sum += now - arr[r]; now += svc; head = cyl[r]; served++;
    }
    return wait_sum / REQ;
}
int main(void) {
    int q[] = {98,183,37,122,14,124,65,67}, n = 8, h = 53, ord[MAXQ];
    puts("== Static algorithms (cylinders 0-199, head 53) ==");
    printf("FCFS   : %d\n", fcfs(h, q, n));
    int s = sstf(h, q, n, ord);
    printf("SSTF   : %d  order:", s); for (int i = 0; i < n; i++) printf(" %d", ord[i]); puts("");
    printf("SCAN   : %d (toward 0 first, includes cylinder 0)\n", scan_down(h, q, n));
    printf("C-SCAN : %d (upward, includes wrap 199->0)\n", cscan_up(h, q, n, 199));
    printf("LOOK   : %d (toward 0 first)\n", look_down(h, q, n));
    printf("C-LOOK : %d (upward, includes circular jump)\n", clook_up(h, q, n));

    puts("\n== SIMULATION (synthetic model, NOT physical measurement) ==");
    puts("model: 10000 requests, exponential arrivals, service = 4 ms + 0.05 ms/cylinder, seed 7");
    double gaps[2] = {8.0, 5.3}; const char *lab[2] = {"medium", "heavy"};
    for (int i = 0; i < 2; i++)
        printf("%-6s load (mean gap %.1f ms): FCFS avg wait %.3f ms | SSTF avg wait %.3f ms\n",
               lab[i], gaps[i], simulate(0, gaps[i], 7), simulate(1, gaps[i], 7));
    return 0;
}
