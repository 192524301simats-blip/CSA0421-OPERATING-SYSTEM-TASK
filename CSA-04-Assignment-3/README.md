# CSA04 – Operating Systems – Assignment 3: Memory Management

Student: J.P. Badri | Register No: 192524301 | Course: CSA 0421

Source programs for the report "Memory Management: Design, Analysis and Implementation".

| Folder | Report question | What it contains |
|---|---|---|
| Task01 | Q1 Linking/Loading | static lib, shared lib, `dlopen`/`dlsym` plugin demo |
| Task02 | Q2 Paging | address translation, page-table size, EAT, fragmentation |
| Task03 | Q3 Segmentation | base/limit checks, child-process fault isolation, fragmentation sim |
| Task04 | Q4 Demand paging | page-fault counting with `getrusage`, copy-on-write after `fork` |
| Task05 | Q5 Page replacement | FIFO, LRU, Optimal, Clock + CSV output |
| Task06 | Q6 Disk management | RAID calculator, read-only disk inspection script |
| Task07 | Q7 2 GB edge device | memory budget, real-time loop (`mlockall`, `SCHED_FIFO`), cgroup script |
| evidence | Checklist | put your own `.txt` outputs / screenshots here |

## Build and run (Linux / WSL)
```bash
make          # builds everything
make run      # runs everything
make clean
```
Compiler flags: `gcc -std=c11 -Wall -Wextra -O2`. Task01 needs `-ldl` (handled by its Makefile).

## Record your own evidence
```bash
gcc --version; uname -a; lsb_release -a; getconf PAGESIZE
make run > evidence/run_output.txt 2>&1
```
Timings, fault counts and fragmentation numbers depend on your machine – report what you measure.
