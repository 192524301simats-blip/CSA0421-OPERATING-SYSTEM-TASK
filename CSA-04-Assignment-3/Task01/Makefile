CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -O2 -D_GNU_SOURCE
all: static_app dynamic_app dl_app
mathlib.o: mathlib.c mathlib.h
	$(CC) $(CFLAGS) -c mathlib.c
libmathlib.a: mathlib.o
	ar rcs $@ mathlib.o
libmathlib.so: mathlib.c
	$(CC) $(CFLAGS) -fPIC -shared mathlib.c -o $@
static_app: main_link.c libmathlib.a
	$(CC) $(CFLAGS) main_link.c -L. -l:libmathlib.a -o $@
dynamic_app: main_link.c libmathlib.so
	$(CC) $(CFLAGS) main_link.c -L. -lmathlib -Wl,-rpath,'$$ORIGIN' -o $@
libcipher.so: plugin_cipher.c
	$(CC) $(CFLAGS) -fPIC -shared plugin_cipher.c -o $@
dl_app: main_dlopen.c libcipher.so
	$(CC) $(CFLAGS) main_dlopen.c -ldl -o $@
run: all
	./static_app && ./dynamic_app && ./dl_app ./libcipher.so
	@echo "--- sizes ---"; ls -l static_app dynamic_app
	@echo "--- ldd ---"; ldd dynamic_app
clean:
	rm -f *.o *.a *.so static_app dynamic_app dl_app
