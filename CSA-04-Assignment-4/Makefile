CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -O2
PROGS=Task02/alloc_calc Task04/disk_scheduling Task05/replication_calc Task06/streaming_calc Task06/cache_sim
all: $(PROGS)
Task04/disk_scheduling: Task04/disk_scheduling.c
	$(CC) $(CFLAGS) $< -o $@ -lm
Task02/alloc_calc: Task02/alloc_calc.c
	$(CC) $(CFLAGS) $< -o $@ -lm
Task06/cache_sim: Task06/cache_sim.c
	$(CC) $(CFLAGS) $< -o $@ -lm
%: %.c
	$(CC) $(CFLAGS) $< -o $@
run: all
	@for p in $(PROGS); do echo "=== $$p ==="; ./$$p; done
clean:
	rm -f $(PROGS)
