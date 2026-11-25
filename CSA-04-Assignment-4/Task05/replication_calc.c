/* Replication overhead and quorum consistency calculations (analytical). */
#include <stdio.h>
int main(void) {
    double raw_tb = 100;
    printf("== Storage overhead for %.0f TB of data ==\n", raw_tb);
    printf("3 replicas       : %.0f TB raw (3.0x)\n", raw_tb * 3);
    printf("erasure 6+3      : %.0f TB raw (1.5x), tolerates 3 losses\n", raw_tb * 9 / 6);
    puts("\n== Quorum rule R + W > N gives strong (ordered) reads ==");
    int N = 3;
    for (int W = 1; W <= N; W++) for (int R = 1; R <= N; R++)
        printf("N=%d W=%d R=%d : %s\n", N, W, R, (R + W > N) ? "strongly consistent" : "eventual (stale reads possible)");
    puts("\nThree replicas survive 2 node failures for reads; writes need W live nodes.");
    return 0;
}
