#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
int main(int argc, char **argv) {
    const char *path = argc > 1 ? argv[1] : "./libcipher.so";
    void *h = dlopen(path, RTLD_NOW);
    if (!h) { fprintf(stderr, "dlopen failed: %s\n", dlerror()); return 1; } /* never fall back silently */
    dlerror();
    const char *(*name)(void) = (const char *(*)(void))dlsym(h, "cipher_name");
    void (*apply)(unsigned char *, size_t, unsigned char) =
        (void (*)(unsigned char *, size_t, unsigned char))dlsym(h, "cipher_apply");
    char *err = dlerror();
    if (err || !name || !apply) { fprintf(stderr, "dlsym failed: %s\n", err ? err : "null"); dlclose(h); return 1; }
    unsigned char msg[] = "hello bank";
    size_t n = strlen((char *)msg);
    printf("Loaded cipher: %s\n", name());
    apply(msg, n, 0x5A);
    printf("Encrypted bytes:");
    for (size_t i = 0; i < n; i++) printf(" %02x", msg[i]);
    apply(msg, n, 0x5A);
    printf("\nDecrypted: %s\n", msg);
    dlclose(h);
    return 0;
}
