CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -O2 -D_GNU_SOURCE
PROGS=Task02/paging Task03/segmentation Task04/demand_paging Task05/page_replacement Task06/raid_calc Task07/memory_budget Task07/rt_control_demo
all: $(PROGS)
	$(MAKE) -C Task01
%: %.c
	$(CC) $(CFLAGS) $< -o $@
run: all
	@for p in $(PROGS); do echo "=== $$p ==="; ./$$p; done
	$(MAKE) -C Task01 run
clean:
	rm -f $(PROGS)
	$(MAKE) -C Task01 clean
