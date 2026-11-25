/* Compare unbuffered write() with buffered fwrite() for 10,000 one-byte writes.
   Run: strace -c ./stdio_vs_syscall   and compare the write counts. */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(void) {
    int fd = open("out_raw.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    for (int i = 0; i < 10000; i++) if (write(fd, "x", 1) != 1) return 1;
    close(fd);
    FILE *f = fopen("out_buf.tmp", "w");
    for (int i = 0; i < 10000; i++) fputc('x', f);
    fclose(f);
    unlink("out_raw.tmp"); unlink("out_buf.tmp");
    puts("done: 10000 raw write() calls vs ~3 buffered write() calls (check with strace -c)");
    return 0;
}
