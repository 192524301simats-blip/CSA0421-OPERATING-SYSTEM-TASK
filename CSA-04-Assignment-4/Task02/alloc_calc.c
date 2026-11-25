/* File-allocation calculations for the 32-camera NVR task. Analytical, not measured. */
#include <stdio.h>
#include <math.h>
int main(void) {
    const double KiB = 1024.0, GiB = KiB*KiB*KiB, MiB = KiB*KiB;
    double bs = 4 * KiB, ptr = 4;

    double blocks = 4 * GiB / bs;
    printf("== 4 GiB file, 4 KiB blocks ==\n");
    printf("blocks                      : %.0f\n", blocks);
    printf("contiguous: reach last block: O(1) (compute offset)\n");
    printf("linked    : pointers followed: ~%.0f\n", blocks - 1);
    printf("indexed   : a few index reads + 1 data read\n");

    double ppb = bs / ptr;
    printf("\n== Index block ==\npointers per block: %.0f\n", ppb);
    double total = 12 + ppb + ppb*ppb + ppb*ppb*ppb;
    printf("inode max data blocks = 12 + %.0f + %.0f^2 + %.0f^3 = %.0f\n", ppb, ppb, ppb, total);
    printf("max file size = %.2f TiB\n", total * bs / (GiB * KiB));

    double disk = 4e12;
    double nblk = disk / bs;
    printf("\n== 4 TB (decimal) disk ==\n");
    printf("blocks            : %.1f million\n", nblk / 1e6);
    printf("bitmap (1 bit/blk): %.1f MiB\n", nblk / 8 / MiB);
    printf("FAT (4 B/entry)   : %.2f GB decimal (%.2f GiB)\n", nblk * 4 / 1e9, nblk * 4 / GiB);

    /* Time-to-offset index for a fixed-duration segment layout. */
    int seg_sec = 60, cams = 32, days = 30;
    double segs = (double)cams * days * 86400 / seg_sec;
    printf("\n== NVR segment index ==\n%d cameras x %d days with %d s segments = %.0f segment files\n",
           cams, days, seg_sec, segs);
    printf("seek to HH:MM:SS -> dir camNN/YYYY-MM-DD/HH/MM.seg, then offset within segment\n");
    return 0;
}
