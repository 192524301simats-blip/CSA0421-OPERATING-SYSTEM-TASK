/* LRU vs LFU cache hit ratio on a Zipf-like video popularity stream (SIMULATED). */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define V 500
#define REQ 100000
static int lru(const int *r, int cap) {
    int id[V], last[V], n = 0, hits = 0;
    for (int i = 0; i < REQ; i++) {
        int k = -1; for (int j = 0; j < n; j++) if (id[j] == r[i]) { k = j; break; }
        if (k >= 0) { hits++; last[k] = i; continue; }
        if (n < cap) { id[n] = r[i]; last[n++] = i; }
        else { int v = 0; for (int j = 1; j < n; j++) if (last[j] < last[v]) v = j; id[v] = r[i]; last[v] = i; }
    } return hits;
}
static int lfu(const int *r, int cap) {
    int id[V], cnt[V], n = 0, hits = 0;
    for (int i = 0; i < REQ; i++) {
        int k = -1; for (int j = 0; j < n; j++) if (id[j] == r[i]) { k = j; break; }
        if (k >= 0) { hits++; cnt[k]++; continue; }
        if (n < cap) { id[n] = r[i]; cnt[n++] = 1; }
        else { int v = 0; for (int j = 1; j < n; j++) if (cnt[j] < cnt[v]) v = j; id[v] = r[i]; cnt[v] = 1; }
    } return hits;
}
int main(void) {
    static int r[REQ]; static double cdf[V];
    double s = 0; for (int i = 0; i < V; i++) { s += 1.0 / pow(i + 1, 1.0); cdf[i] = s; }
    srand(11);
    for (int i = 0; i < REQ; i++) {
        double u = (rand() / (RAND_MAX + 1.0)) * s; int k = 0; while (cdf[k] < u) k++; r[i] = k;
    }
    puts("SIMULATION: 500 videos, Zipf(1.0) popularity, 100000 requests, seed 11");
    puts("cache_videos,LRU_hit_ratio,LFU_hit_ratio");
    int caps[] = {10, 25, 50, 100};
    for (int i = 0; i < 4; i++) printf("%d,%.3f,%.3f\n", caps[i], lru(r, caps[i]) / (double)REQ, lfu(r, caps[i]) / (double)REQ);
    return 0;
}
