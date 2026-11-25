/* Usable capacity / fault tolerance for N disks of size S TB. */
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
    int n = argc > 1 ? atoi(argv[1]) : 6; double s = argc > 2 ? atof(argv[2]) : 4.0;
    printf("%d disks x %.0f TB\n", n, s);
    printf("RAID0 : %.0f TB, no fault tolerance\n", n * s);
    printf("RAID1 : %.0f TB (%d mirror pairs), 1 disk per pair\n", n / 2 * s, n / 2);
    printf("RAID5 : %.0f TB, 1 disk\n", (n - 1) * s);
    printf("RAID6 : %.0f TB, 2 disks\n", (n - 2) * s);
    printf("RAID10: %.0f TB, >=1 disk (depends on which mirror members fail)\n", n / 2 * s);
    return 0;
}
