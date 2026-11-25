/* Used for both static and dynamic (startup-linked) builds. */
#include <stdio.h>
#include "mathlib.h"
int main(void) {
    printf("add(6,7) = %d\n", add(6, 7));
    printf("mul(6,7) = %d\n", mul(6, 7));
    return 0;
}
