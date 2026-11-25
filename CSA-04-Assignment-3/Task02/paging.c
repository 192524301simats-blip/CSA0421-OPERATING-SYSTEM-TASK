/* Paging: address translation, page-table size, EAT with TLB, internal fragmentation. */
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
static void translate(uint32_t A, uint32_t page_size, const int *pt, int n) {
    uint32_t p = A / page_size, d = A % page_size;
    if ((int)p >= n || pt[p] < 0) { printf("VA %6u -> page %u offset %u : INVALID\n", A, p, d); return; }
    printf("VA %6u -> page %u offset %4u -> frame %d -> PA %u\n", A, p, d, pt[p], pt[p] * page_size + d);
}
int main(void) {
    int pt[8] = {5, 2, -1, 7, 0, 3, -1, 1};
    uint32_t tests[] = {0, 1023, 1024, 2500, 3072, 5000, 7167, 9000};
    puts("== Address translation (page size 1024) ==");
    for (int i = 0; i < 8; i++) translate(tests[i], 1024, pt, 8);

    puts("\n== Page-table size ==");
    double e32 = (double)(1ULL << 20) * 4 / (1 << 20);
    double e48 = (double)(1ULL << 36) * 8 / (1024.0 * 1024 * 1024);
    printf("32-bit VA, 4KiB pages, 4B PTE : %.0f MiB per process\n", e32);
    printf("48-bit VA, 4KiB pages, 8B PTE : %.0f GiB flat table\n", e48);

    puts("\n== EAT = h(t+m) + (1-h)(t+2m), t=10ns m=100ns ==");
    double hs[] = {0.80, 0.95, 0.99};
    for (int i = 0; i < 3; i++) printf("hit ratio %.2f -> EAT %.1f ns\n", hs[i], hs[i]*110 + (1-hs[i])*210);

    puts("\n== Expected internal fragmentation, 100 processes (half a page each) ==");
    printf("1 KiB pages: %d KiB\n", 100 * 1 / 2);
    printf("4 KiB pages: %d KiB\n", 100 * 4 / 2);
    printf("2 MiB pages: %d MiB\n", 100 * 2 / 2);

    puts("\n== This machine ==");
    printf("sysconf(_SC_PAGESIZE) = %ld bytes\n", sysconf(_SC_PAGESIZE));
    return 0;
}
