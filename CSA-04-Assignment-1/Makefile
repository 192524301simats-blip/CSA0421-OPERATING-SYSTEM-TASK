CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -O2
PROGS=Task05/system_calls Task05/stdio_vs_syscall Task06/file_copy Task06/mmap_copy Task07/process_control Task07/flush_experiment Task07/zombie_demo Task08/cpu_protection Task09/memory_hierarchy Task10/process_thread_bench
all: $(PROGS)
Task10/process_thread_bench: Task10/process_thread_bench.c
	$(CC) $(CFLAGS) $< -o $@ -pthread
%: %.c
	$(CC) $(CFLAGS) $< -o $@
run: all
	cd Task05 && ./system_calls && ./stdio_vs_syscall
	cd Task06 && ./file_copy && ./mmap_copy
	cd Task07 && ./process_control
	cd Task08 && ./cpu_protection
	cd Task09 && ./memory_hierarchy
	./Task10/process_thread_bench
clean:
	rm -f $(PROGS) *.tmp */*.tmp */*.dat
