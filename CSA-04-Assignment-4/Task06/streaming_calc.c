/* Video-streaming storage sizing (analytical). Targets are proposals, not measurements. */
#include <stdio.h>
int main(void) {
    double streams = 10000, mbps = 5;
    printf("Delivery bandwidth: %.0f streams x %.0f Mbit/s = %.0f Gbit/s\n", streams, mbps, streams * mbps / 1000);
    double videos = 500, avg_gb = 1;
    printf("Catalogue: %.0f videos x %.0f GB = %.0f GB raw; 2 copies = %.1f TB\n", videos, avg_gb, videos * avg_gb, 2 * videos * avg_gb / 1000);
    double seg_mib = 8;
    printf("Seek waste with %.0f MiB segments: < %.0f MiB (one segment)\n", seg_mib, seg_mib);
    double bitrate_mb_s = mbps / 8;
    printf("One 5 Mbit/s stream = %.3f MB/s; one 8 MiB segment = %.1f s of video\n", bitrate_mb_s, seg_mib * 1.048576 / bitrate_mb_s);
    double hot_gb = 50 * avg_gb;
    printf("Hot SSD cache for top 50 first-week videos: ~%.0f GB\n", hot_gb);
    return 0;
}
