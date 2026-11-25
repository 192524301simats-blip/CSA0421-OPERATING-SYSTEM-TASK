/* Optional "algorithm" loaded at run time with dlopen (toy XOR, NOT real crypto). */
#include <stddef.h>
const char *cipher_name(void) { return "toy-xor-v1"; }
void cipher_apply(unsigned char *buf, size_t n, unsigned char key) {
    for (size_t i = 0; i < n; i++) buf[i] ^= key;
}
