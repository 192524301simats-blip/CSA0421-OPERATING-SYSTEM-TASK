# CSA04 – Operating Systems – Assignment 4: Optimising File Storage and Disk Access

Student: J.P. Badri | Register No: 192524301 | Course: CSA 0421

| Folder | Report task | Contents |
|---|---|---|
| Task01 | File-system design review | `setup_student_tree.sh` – builds the cohort/register directory layout with 0700 / setgid permissions |
| Task02 | 32-camera NVR allocation | `alloc_calc.c` – block counts, inode limit, bitmap/FAT size, segment index |
| Task03 | Modern file systems | `fs_inspect.sh` – read-only stat / df -i / findmnt / tune2fs collection |
| Task04 | Disk scheduling | `disk_scheduling.c` (FCFS, SSTF, SCAN, C-SCAN, LOOK, C-LOOK + seeded simulation), `scheduler_check.sh` |
| Task05 | Distributed/cloud storage | `replication_calc.c` – replica overhead and quorum consistency |
| Task06 | Video-streaming design | `streaming_calc.c`, `cache_sim.c` (LRU vs LFU), `fio_streaming.fio` |
| evidence | Checklist | your own screenshots and outputs |

## Build and run (Linux / WSL)
```bash
make && make run
bash Task01/setup_student_tree.sh ./demo_student_data
bash Task03/fs_inspect.sh .
bash Task04/scheduler_check.sh
```
Only run `fio` on a dedicated test directory (edit `directory=` in the job file first).

## Simulated vs measured
`disk_scheduling.c` (event simulation) and `cache_sim.c` are **simulations** with the stated synthetic
assumptions; they are not physical disk measurements. Record real fio/scheduler results in `evidence/`.
