/* Admission check for the 2 GB edge device (values in MB; edit to match your measurements). */
#include <stdio.h>
int main(void) {
    struct { const char *name; int mb; } t[] = {
        {"kernel+drivers+DMA reserve", 300}, {"real-time control (locked)", 64},
        {"ML task", 1500}, {"logger (bounded)", 64}, {"safety margin", 100}};
    int total = 2048, used = 0;
    for (unsigned i = 0; i < sizeof t / sizeof t[0]; i++) { printf("%-30s %5d MB\n", t[i].name, t[i].mb); used += t[i].mb; }
    printf("%-30s %5d MB\n%-30s %5d MB\n", "used", used, "free", total - used);
    int extra = 500;
    printf("Admit extra %d MB task? %s\n", extra, (total - used >= extra) ? "YES" : "NO - reduce ML residency, stream/offload, or add RAM");
    return 0;
}
