# CSA04 – Operating Systems – Assignment 1: Smart Hospital OS Design

Student: J.P. Badri | Register No: 192524301 | Course: CSA 0421

Tasks 1-4, 11 and 12 are analytical design tasks and are answered in the report (no code needed).
Tasks 5-10 have source code in this repository.

| Folder | Report task | Programs |
|---|---|---|
| Task05 | System calls | `system_calls.c` (+ `sample.txt`), `stdio_vs_syscall.c` (buffered vs raw writes) |
| Task06 | Cost of system calls | `file_copy.c` (10001 / 21 / 4 read calls), `mmap_copy.c` |
| Task07 | Process control | `process_control.c`, `flush_experiment.c` (stdout flush before fork), `zombie_demo.c` |
| Task08 | CPU states and protection | `cpu_protection.c` (privileged-instruction trap, timer interrupt, polling delay) |
| Task09 | Memory hierarchy and I/O | `memory_hierarchy.c` (latency vs working-set size, interrupt-per-word vs DMA) |
| Task10 | Measure and compare | `process_thread_bench.c`, `run_all.sh` (collects evidence) |
| evidence | Required outputs | your screenshots / saved outputs |

## Build and run (Linux / WSL)
```bash
make          # compile all with gcc -std=c11 -Wall -Wextra -O2
make run
bash Task10/run_all.sh     # saves evidence/task10_results.txt (needs strace)
```
## Notes
- Timings (Task09, Task10) are machine-dependent: record your own numbers, do not copy another machine's.
- `Task08/cpu_protection.c` executes the x86 `cli` instruction in a child process to show the CPU trapping it; it is harmless (the child is killed).
- `Task07/flush_experiment.c`: run `./flush_experiment > out.txt; cat out.txt` to see the duplicated line.
