/* Alternative: copy a file using mmap() instead of repeated read() calls. */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
int main(void) {
    FILE *f = fopen("records.dat", "w");
    if (!f) { perror("fopen"); return 1; }
    for (int i = 0; i < 10000; i++) fputc('A' + i % 26, f);
    fclose(f);
    int in = open("records.dat", O_RDONLY);
    struct stat st; if (fstat(in, &st) < 0) { perror("fstat"); return 1; }
    char *src = mmap(NULL, (size_t)st.st_size, PROT_READ, MAP_PRIVATE, in, 0);
    if (src == MAP_FAILED) { perror("mmap"); return 1; }
    int out = open("copy_mmap.dat", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    ssize_t w = write(out, src, (size_t)st.st_size);   /* one write for the whole mapping */
    printf("mmap copy wrote %zd of %lld bytes\n", w, (long long)st.st_size);
    munmap(src, (size_t)st.st_size); close(in); close(out);
    unlink("records.dat"); unlink("copy_mmap.dat");
    return 0;
}
