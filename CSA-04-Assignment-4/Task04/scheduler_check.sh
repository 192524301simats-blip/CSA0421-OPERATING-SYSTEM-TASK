#!/usr/bin/env bash
# Show the I/O scheduler for each block device (read-only).
lsblk -d -o NAME,ROTA,SIZE,TYPE
for f in /sys/block/*/queue/scheduler; do echo "$f: $(cat "$f")"; done
