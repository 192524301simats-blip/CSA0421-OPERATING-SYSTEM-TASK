/* FIFO, LRU, Optimal, Clock. Part 1: textbook strings. Part 2: CSV for synthetic streams. */
#include <stdio.h>
#include <stdlib.h>
#define MAXF 16
static int find(const int *fr, int nf, int pg) { for (int i = 0; i < nf; i++) if (fr[i] == pg) return i; return -1; }
int fifo(const int *r, int n, int nf) {
    int fr[MAXF], used = 0, hand = 0, f = 0;
    for (int i = 0; i < n; i++) {
        if (find(fr, used, r[i]) >= 0) continue;
        f++; if (used < nf) fr[used++] = r[i]; else { fr[hand] = r[i]; hand = (hand + 1) % nf; }
    } return f;
}
int lru(const int *r, int n, int nf) {
    int fr[MAXF], last[MAXF], used = 0, f = 0;
    for (int i = 0; i < n; i++) {
        int k = find(fr, used, r[i]);
        if (k >= 0) { last[k] = i; continue; }
        f++;
        if (used < nf) { fr[used] = r[i]; last[used++] = i; }
        else { int v = 0; for (int j = 1; j < nf; j++) if (last[j] < last[v]) v = j; fr[v] = r[i]; last[v] = i; }
    } return f;
}
int opt(const int *r, int n, int nf) {
    int fr[MAXF], used = 0, f = 0;
    for (int i = 0; i < n; i++) {
        if (find(fr, used, r[i]) >= 0) continue;
        f++;
        if (used < nf) { fr[used++] = r[i]; continue; }
        int v = 0, far = -1;
        for (int j = 0; j < nf; j++) {
            int nx = n; for (int k = i + 1; k < n; k++) if (r[k] == fr[j]) { nx = k; break; }
            if (nx > far) { far = nx; v = j; }
        }
        fr[v] = r[i];
    } return f;
}
int clockalg(const int *r, int n, int nf) {
    int fr[MAXF], ref[MAXF], used = 0, hand = 0, f = 0;
    for (int i = 0; i < n; i++) {
        int k = find(fr, used, r[i]);
        if (k >= 0) { ref[k] = 1; continue; }
        f++;
        if (used < nf) { fr[used] = r[i]; ref[used++] = 1; continue; }
        while (ref[hand]) { ref[hand] = 0; hand = (hand + 1) % nf; }
        fr[hand] = r[i]; ref[hand] = 1; hand = (hand + 1) % nf;
    } return f;
}
int main(void) {
    int s20[] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    int bel[] = {1,2,3,4,1,2,5,1,2,3,4,5};
    puts("== 20-reference string ==");
    for (int nf = 3; nf <= 4; nf++)
        printf("frames=%d FIFO=%d LRU=%d OPT=%d CLOCK=%d\n", nf, fifo(s20,20,nf), lru(s20,20,nf), opt(s20,20,nf), clockalg(s20,20,nf));
    puts("\n== Belady string (FIFO) ==");
    for (int nf = 3; nf <= 4; nf++) printf("frames=%d FIFO=%d\n", nf, fifo(bel,12,nf));

    puts("\n== CSV (seed=1, 2000 refs, 50 pages) ==");
    enum { N = 2000, PAGES = 50 };
    static int loc[N], uni[N];
    srand(1);
    int base = 0;
    for (int i = 0; i < N; i++) {
        if (i % 100 == 0) base = rand() % (PAGES - 8);
        loc[i] = base + rand() % 8; uni[i] = rand() % PAGES;
    }
    puts("stream,frames,FIFO,LRU,OPT,CLOCK");
    for (int nf = 3; nf <= 10; nf++) {
        printf("locality,%d,%d,%d,%d,%d\n", nf, fifo(loc,N,nf), lru(loc,N,nf), opt(loc,N,nf), clockalg(loc,N,nf));
        printf("uniform,%d,%d,%d,%d,%d\n", nf, fifo(uni,N,nf), lru(uni,N,nf), opt(uni,N,nf), clockalg(uni,N,nf));
    }
    return 0;
}
